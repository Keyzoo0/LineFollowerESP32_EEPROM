
void guiCalSensor() {
  oledClear();
  while (1) {
    headUp(true, false);
    if (touchUp(Button_RUN)) {
      oledClear();
      saveAll();
      break;
    }

    if (touchUp(Button_UP)) {
      delay(10);
      calibAuto();
      lcd.fillRoundRect(25, 25, 25, 10, 2, SH110X_WHITE);
      lcd_char(1, 26, 26, "Auto", false, false, false);
    } else {
      lcd.drawRoundRect(25, 25, 25, 10, 2, SH110X_WHITE);
      lcd_char(1, 26, 26, "Auto", true, false, false);
    }

    if (touchUp(Button_PLUS)) {
      countMenu = 1;
      calibManual();
      lcd.fillRoundRect(55, 25, 38, 10, 2, SH110X_WHITE);
      lcd_char(1, 57, 26, "Manual", false, false, false);
    } else {
      lcd.drawRoundRect(55, 25, 38, 10, 2, SH110X_WHITE);
      lcd_char(1, 57, 26, "Manual", true, false, false);
    }
    lcd.display();
  } // end while calib bracket
}


void calibAuto(){
byte _stepsCalib;
lcd.clearDisplay();
delay(10);
      while (1) {
        headUp(true, false);
        if (touchUp(Button_RUN)) {
          _stepsCalib = 0;
          lcd.clearDisplay();
          break;
        }

        if (touchUp(Button_OK)) {
          _stepsCalib++;
        }

        if (_stepsCalib == 0) {
          if (touchDown(Button_PLUS,100)) {
            sensorSensivity++;
            if (sensorSensivity > 100) sensorSensivity = 0;
            saveSensorSens();
          }
          if (touchDown(Button_MIN,100)) {
            sensorSensivity--;
            if (sensorSensivity == 255) sensorSensivity = 100;
            saveSensorSens();
          }
          sprintf(buff, "Set Sensivity : %d", sensorSensivity);
          lcd_char(1, 2, 16, buff, true, false, false);
        }

        else if (_stepsCalib == 1) {
          for (byte i = 0; i < MAXSENSOR; i++) {
            setMinVal[i] = setMinVal[i] = 1023;
            setMaxVal[i] = setMaxVal[i] = 0;
          }
          delayMicroseconds(500);
          while (1) {
            headUp(true, false);
            dispSensor(0xFFFF);
            lcd_char(1, 35 , 40, "Scanning!!", true, false, false);
            int buffSens = readSensor();
            for (int x = 0; x < MAXSENSOR; x++) {
              if (adcVal[x] > setMaxVal[x]) {
                setMaxVal[x] = adcVal[x];
              }
              if (adcVal[x] < setMinVal[x]) {
                setMinVal[x] = adcVal[x];
              }
            }
            lcd.display();
            if (touchUp(Button_OK)) {
              delay(50);
              _stepsCalib = 2;
              break;
            }
          }
        } // steps 1
        else if (_stepsCalib == 2) {
          for (int i = 0; i < MAXSENSOR; i++) {
            CalAdc[i] = ((setMaxVal[i] - setMinVal[i]) * (float)((100.0 - sensorSensivity) / 100.0)) + setMinVal[i];
          }
          lcd_char(1, 2, 16, "Success Calibration", true, false, false);
          sprintf(buff, "Sensor %d : %u" , sens, CalAdc[sens]);
          lcd_char(1, 2, 32, buff, true, false, false);
          saveCalib();
          saveMaxMinSens();
          delay(300);
          sens++;
          if(sens > 13) sens = 0;
        }
        lcd.display();
      } 
  }

void calibManual(){
  selectSet = 0;
      while(1){
        headUp(true, false);
        dispSensor(readSensor());
        if(touchUp(Button_RUN)){
          saveAll();
          oledClear();
          break;
        }
        if(touchDown(Button_UP , 200)){
          selectSet = 0;
          if(++countMenu > 14) countMenu = 1;
        }
        if(touchDown(Button_DOWN , 200)){
          selectSet = 0;
          if(--countMenu < 1 ) countMenu = 14;
        }
        if(touchUp(Button_OK)){
         if(++selectSet > 4 ) selectSet = 1;
        }

        if(selectSet == 1){
          lcd.drawRoundRect(0, 38, 53, 12, 2, SH110X_WHITE);
          if(touchDown(Button_PLUS , 100)){
            setMaxVal[countMenu - 1]++;
            if(setMaxVal[countMenu - 1] > 1023) setMaxVal[countMenu - 1] = 1023;
          }
          if(touchDown(Button_MIN ,  100)){
            setMaxVal[countMenu - 1]--;
            if(setMaxVal[countMenu - 1] < 0) setMaxVal[countMenu - 1] = 0;
          }
        }
        else if(selectSet == 2){
          lcd.drawRoundRect(0, 48, 53, 12, 2, SH110X_WHITE);
          if(touchDown(Button_PLUS , 100)){
            setMinVal[countMenu - 1]++;
            if(setMinVal[countMenu - 1] > 1023) setMinVal[countMenu - 1] = 1023;
          }
          if(touchDown(Button_MIN , 100)){
            setMinVal[countMenu - 1]--;
            if(setMinVal[countMenu - 1] < 0) setMinVal[countMenu - 1] = 0;
          }
        }
        else if(selectSet == 3){
          lcd.drawRoundRect(56, 38, 65, 12, 2, SH110X_WHITE);
        }
        else if(selectSet == 4){
          lcd.drawRoundRect(56, 48, 65, 12, 2, SH110X_WHITE);
          if(touchDown(Button_PLUS , 100)){
            CalAdc[countMenu - 1]++;
            if(CalAdc[countMenu - 1] > 1024) CalAdc[countMenu - 1] = 1024;
          }
          if(touchDown(Button_MIN , 100)){
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
}