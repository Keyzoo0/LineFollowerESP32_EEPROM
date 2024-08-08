
// Inisialisasi Kalman Filter untuk setiap saluran
int muxChannel[8][3] = {
  {0, 0, 0},
  {1, 0, 0},
  {0, 1, 0},
  {1, 1, 0},
  {0, 0, 1},
  {1, 0, 1},
  {0, 1, 1},
  {1, 1, 1}
};

void setupSensor() {
  pinMode(S1_MUX, OUTPUT);
  pinMode(S2_MUX, OUTPUT);
  pinMode(S3_MUX, OUTPUT);
  pinMode(MUX_Kiri_ADC1, INPUT_PULLUP);
  pinMode(MUX_Kanan_ADC2, INPUT_PULLUP);
  pinMode(ADCBAT, INPUT);
  analogReadResolution(12);
}

unsigned long prevLed = 0;
void ILED(int Tim) {
  if (millis() - prevLed >= Tim) {
    SLED(1);
    prevLed = millis();
  }
  SLED(0);
}

void readMux(byte i) {
  digitalWrite(S1_MUX, muxChannel[i][0]);
  digitalWrite(S2_MUX, muxChannel[i][1]);
  digitalWrite(S3_MUX, muxChannel[i][2]);
}

int readSensor() {
  int16_t bitMask = 0b00000000000000;
  int16_t bitBuf = 0b11111111111111;
//  for (byte i = 0; i < 8; i++) {
//    readMux(i);
// //    i == 0 ? adcVal[7] = analogRead(MUX_Kanan_ADC2) : adcVal[i + 7] = analogRead(MUX_Kanan_ADC2);
// //    i == 7 ? adcVal[6] = analogRead(MUX_Kiri_ADC1) : adcVal[i - 1] = analogRead(MUX_Kiri_ADC1);
//    if(i == 0) adcVal[7] = analogRead(MUX_Kanan_ADC2);
//    else if (i == 7) adcVal[6] == analogRead(MUX_Kiri_ADC1);
//    else {
//      adcVal[i+7] = analogRead(MUX_Kanan_ADC2);
//      adcVal[i-1] = analogRead(MUX_Kiri_ADC1);
//    }
//  }

  readMux(0);
  adcVal[7] = analogRead(MUX_Kanan_ADC2);
  readMux(1);
  adcVal[6] = analogRead(MUX_Kiri_ADC1);
  adcVal[8] = analogRead(MUX_Kanan_ADC2);
  readMux(2);
  adcVal[5] = analogRead(MUX_Kiri_ADC1);
  adcVal[9] = analogRead(MUX_Kanan_ADC2);
  readMux(3);
  adcVal[4] = analogRead(MUX_Kiri_ADC1);
  adcVal[10] = analogRead(MUX_Kanan_ADC2);
  readMux(4);
  adcVal[3] = analogRead(MUX_Kiri_ADC1);
  adcVal[11] = analogRead(MUX_Kanan_ADC2);
  readMux(5);
  adcVal[2] = analogRead(MUX_Kiri_ADC1);
  adcVal[12] = analogRead(MUX_Kanan_ADC2);
  readMux(6);
  adcVal[1] = analogRead(MUX_Kiri_ADC1);
  adcVal[13] = analogRead(MUX_Kanan_ADC2);
  readMux(7);
  adcVal[0] = analogRead(MUX_Kiri_ADC1);

  for (byte i = 0; i < 7; i++) {
      // Filter nilai ADC menggunakan Kalman Filter
    filteredVal[i * 2] = kalmanFilters[i * 2].updateEstimate(adcVal[i * 2]);
    filteredVal[i * 2 + 1] = kalmanFilters[i * 2 + 1].updateEstimate(adcVal[i * 2 + 1]);

  }
  
  // for (byte i = 0; i < MAXSENSOR; i++) {
  //   if (adcVal[i] > CalAdc[i]) bitMask = bitMask + (0b10000000000000 >> i);
  // }
  for (byte i = 0; i < MAXSENSOR; i++) {
    if (filteredVal[i] > CalAdc[i]) bitMask = bitMask + (0b10000000000000 >> i);
  }
  if (clrLinePlay == 1) {
    bitBuf = ~(0b11111111111111 - bitMask);
  } else {
    bitBuf = ~bitMask;
  }
  return bitBuf;
}

uint16_t estimatePosition(){
  uint32_t avg = 0; 
  uint16_t sum = 0;
  for(byte i = 0; i < MAXSENSOR; i++){
    uint16_t values = adcVal[i];
    avg += (uint32_t) values * (i * 1000);
    sum += values;
  }
  return avg / sum; 
}

float readBattery() {
  float adcVal_Bat = analogRead(ADCBAT);
  float valueAdc = (3.3f / 1023.0f) * ((10000 + 3300) / 3300);
  float vout = adcVal_Bat * valueAdc / 70;
  return vout;
}

