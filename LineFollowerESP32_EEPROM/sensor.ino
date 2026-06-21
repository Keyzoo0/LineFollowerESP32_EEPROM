// ===========================================================================
// Sensor garis (14 IR via 2x MUX) + baterai.
// Perbaikan: resolusi ADC 10-bit (0..1023) — konsisten dengan rentang kalibrasi
// (dulu analogReadResolution(8) tapi kalibrasi memakai skala 1023 -> mismatch).
// ===========================================================================

void setupSensor() {
  pinMode(S1_MUX, OUTPUT);
  pinMode(S2_MUX, OUTPUT);
  pinMode(S3_MUX, OUTPUT);
  pinMode(MUX_Kiri_ADC1, INPUT);
  pinMode(MUX_Kanan_ADC2, INPUT);
  pinMode(ADCBAT, INPUT);
  analogReadResolution(10);          // 0..1023
}

static int readMuxL(int channel) {
  static const int ctrl[3] = {S1_MUX, S2_MUX, S3_MUX};
  for (int i = 0; i < 3; i++) digitalWrite(ctrl[i], (channel >> i) & 0x01);
  return analogRead(MUX_Kiri_ADC1);
}

static int readMuxR(int channel) {
  static const int ctrl[3] = {S1_MUX, S2_MUX, S3_MUX};
  for (int i = 0; i < 3; i++) digitalWrite(ctrl[i], (channel >> i) & 0x01);
  return analogRead(MUX_Kanan_ADC2);
}

// Baca 14 sensor -> bitmask 14-bit (bit13 = sensor paling kiri).
int readSensor() {
  int16_t bitMask = 0;

  adcVal[0] = readMuxL(6);
  adcVal[1] = readMuxL(5);
  adcVal[2] = readMuxL(4);
  adcVal[3] = readMuxL(3);
  adcVal[4] = readMuxL(2);
  adcVal[5] = readMuxL(1);
  adcVal[6] = readMuxL(0);

  adcVal[7]  = readMuxR(0);
  adcVal[8]  = readMuxR(1);
  adcVal[9]  = readMuxR(2);
  adcVal[10] = readMuxR(3);
  adcVal[11] = readMuxR(4);
  adcVal[12] = readMuxR(5);
  adcVal[13] = readMuxR(6);

  for (byte i = 0; i < MAXSENSOR; i++) {
    if (adcVal[i] > CalAdc[i]) bitMask |= (0b10000000000000 >> i);
  }
  return bitMask;
}

float readBattery() {
  static float filteredValue = 0;
  static unsigned long lastSampleTime = 0;
  const float alpha = 0.01;
  const unsigned long sampleInterval = 5;

  if (millis() - lastSampleTime >= sampleInterval) {
    lastSampleTime = millis();
    float adc   = analogRead(ADCBAT);
    float vout  = (adc / 1023.0f) * 3.3f;
    float ratio = (10000.0f + 3300.0f) / 3300.0f;
    float vbat  = vout * ratio;
    if (filteredValue == 0) filteredValue = vbat;
    else filteredValue = alpha * vbat + (1 - alpha) * filteredValue;
  }
  return (filteredValue < 5) ? 0 : filteredValue;
}

// Bar sensor di layar Home (spasi 9 px).
void displaySensor(unsigned int sens) {
  for (int i = 0; i < 14; i++) {
    if ((sens << i) & 0b10000000000000) {
      lcd.fillRect(3 + (9 * i), 15, 5, 8, SH110X_WHITE);
      lcd.fillRect(2 + (9 * i), 23, 7, 1, SH110X_WHITE);
    } else {
      lcd.fillRect(2 + (9 * i), 23, 7, 1, SH110X_WHITE);
    }
  }
}
