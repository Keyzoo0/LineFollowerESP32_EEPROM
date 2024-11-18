

void setupSensor() {
  pinMode(S1_MUX, OUTPUT);
  pinMode(S2_MUX, OUTPUT);
  pinMode(S3_MUX, OUTPUT);
  pinMode(MUX_Kiri_ADC1, INPUT);
  pinMode(MUX_Kanan_ADC2, INPUT);
  pinMode(ADCBAT, INPUT);
  analogReadResolution(8);
}

unsigned long prevLed = 0;
void ILED(int Tim) {
  if (millis() - prevLed >= Tim) {
    SLED(1);
    prevLed = millis();
  }
  SLED(0);
}

void selector(boolean a, boolean b, boolean  c) {
  digitalWrite(S1_MUX, a);
  digitalWrite(S2_MUX, b);
  digitalWrite(S3_MUX, c);
}

int readMuxL(int channel) {
  int controlPin[] = {S1_MUX, S2_MUX, S3_MUX};
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
  for (int i = 0; i < 3; i ++) {
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  int val = analogRead(MUX_Kiri_ADC1);
  return val;
}


int readMuxR(int channel) {
  int controlPin[] = {S1_MUX, S2_MUX, S3_MUX};
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
  for (int i = 0; i < 3; i ++) {
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  int val = analogRead(MUX_Kanan_ADC2);
  return val;
}


int readSensor() {
  int16_t bitMask = 0b00000000000000;
 
  // adcVal 0 1 2 3 4 5 6 | 7 8 9 10 11 12 13

  //scan kiri
  adcVal[0] = readMuxL(6); 
  adcVal[1] = readMuxL(5); 
  adcVal[2] = readMuxL(4); 
  adcVal[3] = readMuxL(3); 
  adcVal[4] = readMuxL(2); 
  adcVal[5] = readMuxL(1); 
  adcVal[6] = readMuxL(0); 

  //scan kanan
  adcVal[7]  = readMuxR(0); 
  adcVal[8]  = readMuxR(1); 
  adcVal[9]  = readMuxR(2); 
  adcVal[10] = readMuxR(3); 
  adcVal[11] = readMuxR(4); 
  adcVal[12] = readMuxR(5); 
  adcVal[13] = readMuxR(6); 

  
  for (byte i = 0; i < MAXSENSOR; i++) {
    if (adcVal[i] > CalAdc[i]) bitMask = bitMask + (0b10000000000000 >> i);
  }
  
  return bitMask;

}
float readBattery() {
  static float filteredValue = 0;  // Nilai awal filter
  static unsigned long lastSampleTime = 0; // Waktu terakhir pembaruan
  const float alpha = 0.01; // Faktor peredaman (nilai 0-1, 0.1 memberikan stabilisasi ringan)
  const unsigned long sampleInterval = 5; // Interval pengambilan sampel dalam milidetik

  // Cek apakah waktu saat ini sudah melebihi interval pengambilan sampel
  if (millis() - lastSampleTime >= sampleInterval) {
    lastSampleTime = millis(); // Perbarui waktu terakhir pengambilan sampel

    // Baca nilai ADC dan konversi ke tegangan
    float adcVal_Bat = analogRead(ADCBAT);
    float vout = (adcVal_Bat / 255.0f) * 3.3f;
    float ratio = (10000.0f + 3300.0f) / 3300.0f;
    float vbat = vout * ratio;

    // Terapkan filter EMA
    if (filteredValue == 0) {
      filteredValue = vbat; // Inisialisasi nilai pertama jika belum diatur
    } else {
      filteredValue = alpha * vbat + (1 - alpha) * filteredValue;
    }
  }

  // Kembalikan nilai hasil filter yang stabil
  if (filteredValue < 5) {
    return 0;
  } else {
    return filteredValue;
  }
}


void displaySensor(unsigned int sens) {

  for (int i = 0; i < 14; i++) {
    if ((sens << i) & 0b10000000000000) {
      lcd.fillRect(3 + (9 * i), 15, 5, 8, SH110X_WHITE);
      lcd.fillRect(2 + (9 * i), 15 + 8, 7, 1, SH110X_WHITE);
    } else {
      lcd.fillRect(2 + (9 * i), 15 + 8, 7, 1, SH110X_WHITE);
    }
  }
}


void calibSensor() {
  oledClear();
  countMenu = 0;
  byte _stepsCalib;
  while (1) {
    headUp(true, false);
    if (touchUp(Button_RUN)) {
      oledClear();
      saveAll();
      break;
    }

    if (touchUp(Button_UP)) {
      calibAuto();
      // end while bracket
      lcd.fillRoundRect(25, 25, 25, 10, 2, SH110X_WHITE);
      lcd_char(1, 26, 26, "Auto", false, false, false);
    } else {
      lcd.drawRoundRect(25, 25, 25, 10, 2, SH110X_WHITE);
      lcd_char(1, 26, 26, "Auto", true, false, false);
    }

    if (touchUp(Button_PLUS)) {
      countMenu = 1;
      selectSet = 0;
      while(1){
        headUp(true, false);
        dispSensor(readSensor());
        if(touchUp(Button_RUN)){
          saveAll();
          oledClear();
          break;
        }
        if(touchUp(Button_UP)){
          selectSet = 0;
          if(++countMenu > 14) countMenu = 14;
        }
        if(touchUp(Button_DOWN)){
          selectSet = 0;
          if(--countMenu < 1 ) countMenu = 1;
        }
        if(touchUp(Button_OK)){
         if(++selectSet > 4 ) selectSet = 1;
        }

        if(selectSet == 1){
          lcd.drawRoundRect(0, 38, 53, 12, 2, SH110X_WHITE);
          if(touchUp(Button_PLUS)){
            setMaxVal[countMenu - 1]++;
            if(setMaxVal[countMenu - 1] > 1023) setMaxVal[countMenu - 1] = 1023;
          }
          if(touchUp(Button_MIN)){
            setMaxVal[countMenu - 1]--;
            if(setMaxVal[countMenu - 1] < 0) setMaxVal[countMenu - 1] = 0;
          }
        }
        else if(selectSet == 2){
          lcd.drawRoundRect(0, 48, 53, 12, 2, SH110X_WHITE);
          if(touchUp(Button_PLUS)){
            setMinVal[countMenu - 1]++;
            if(setMinVal[countMenu - 1] > 1023) setMinVal[countMenu - 1] = 1023;
          }
          if(touchUp(Button_MIN)){
            setMinVal[countMenu - 1]--;
            if(setMinVal[countMenu - 1] < 0) setMinVal[countMenu - 1] = 0;
          }
        }
        else if(selectSet == 3){
          lcd.drawRoundRect(56, 38, 65, 12, 2, SH110X_WHITE);
        }
        else if(selectSet == 4){
          lcd.drawRoundRect(56, 48, 65, 12, 2, SH110X_WHITE);
          if(touchUp(Button_PLUS)){
            CalAdc[countMenu - 1]++;
            if(CalAdc[countMenu - 1] > 1024) CalAdc[countMenu - 1] = 1024;
          }
          if(touchUp(Button_MIN)){
            CalAdc[countMenu - 1]--;
            if(CalAdc[countMenu - 1] < 0) CalAdc[countMenu - 1] = 0;
          }
        }
        lcd_char(1, 2, 40, "MAX :" + String(setMaxVal[countMenu - 1]), true, false, false);
        lcd_char(1, 2, 50, "MIN :" + String(setMinVal[countMenu - 1]), true, false, false);
        lcd_char(1, 58, 40, "READ :" + String(adcVal[countMenu - 1]), true, false, false);
        lcd_char(1, 58, 50, "SET  :" + String(CalAdc[countMenu - 1]), true, false, false);
        lcd.setCursor(17 + (7 * (countMenu - 1)), 30);
        lcd.write(0x1E);
        lcd.display();
      }
      lcd.fillRoundRect(55, 25, 38, 10, 2, SH110X_WHITE);
      lcd_char(1, 57, 26, "Manual", false, false, false);
    } else {
      lcd.drawRoundRect(55, 25, 38, 10, 2, SH110X_WHITE);
      lcd_char(1, 57, 26, "Manual", true, false, false);
    }
    lcd.display();
  } // end while calib bracket
}


