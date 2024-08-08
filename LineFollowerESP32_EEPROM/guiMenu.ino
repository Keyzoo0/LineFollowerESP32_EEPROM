void menu() {
  countMenu = 1;
  halaman = 0 ;
  saveAll();
  delay(10);
  while (1) {
    stopMotor();
    if (touchUp(Button_UP) ) {
      if (countMenu == 1 && halaman == 0 ) {
        countMenu = 5;
        halaman = 1;
        oledClear();
      }
      if (countMenu == 1  && halaman == 1 ) {
        countMenu = 5;
        halaman = 0;
        oledClear();
      }
      countMenu--;
    }
    if (touchUp(Button_DOWN)) {
       if (countMenu == 4 && halaman == 0 ) {
        countMenu = 0;
        halaman = 1;
        oledClear();
      }
      if (countMenu == 4 && halaman == 1 ) {
        countMenu = 0;
        halaman = 0;
        oledClear();
      }
      countMenu++;
    }

    if (touchUp(Button_RUN)) {
      oledClear();
      break;
    }

    if (halaman == 0) {
      headUp(true, false);
      if (countMenu == 1) {
        if (touchUp(Button_OK)) {
          setIDX();
        }
        lcd.fillRect(0, 14, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 15, "1. Setting Index", false, false, false);
      } else {
        lcd_char(1, 2, 15, "1. Setting Index", true, false, false);
      }

      if (countMenu == 2) {
        if (touchUp(Button_OK)) {
          guiCalSensor();
        }
        lcd.fillRect(0, 24, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 27, "2. Kalibrasi Sensor", false, false, false);
      } else {
        lcd_char(1, 2, 27, "2. Kalibrasi Sensor", true, false, false);
      }

      if (countMenu == 3) {
        if (touchUp(Button_OK)) {
          TunePid();
        }
        lcd.fillRect(0, 34, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 37, "3. Tuning PID", false, false, false);
      } else {
        lcd_char(1, 2, 37, "3. Tuning PID", true, false, false);
      }

      if (countMenu == 4) {
        if (touchUp(Button_OK)) {
          CMIDX();
        }
        lcd.fillRect(0, 44, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 47, "4. Copy/Mirror Plan", false, false, false);
      } else {
        lcd_char(1, 2, 47, "4. Copy/Mirror Plan", true, false, false);
      }
    } else if (halaman == 1) {
      headUp(true, false);
      if (countMenu == 1) {
        if (touchUp(Button_OK)) {
          guiTestMotor();
        }
        lcd.fillRect(0, 14, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 15, "5. Motor", false, false, false);
      } else {
        lcd_char(1, 2, 15, "5. Motor", true, false, false);
      }

      if (countMenu == 2) {
        if (touchUp(Button_OK)) {
          guiResetPlan();
        }
        lcd.fillRect(0, 24, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 27, "6. Reset Plan", false, false, false);
      } else {
        lcd_char(1, 2, 27, "6. Reset Plan", true, false, false);
      }

      if (countMenu == 3) {
        if (touchUp(Button_OK)) {
          guiTransferPlan();
        }
        lcd.fillRect(0, 34, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 37, "7. Transfer Plan", false, false, false);
      } else {

        lcd_char(1, 2, 37, "7. Transfer Plan", true, false, false);
      }

      if (countMenu == 4) {
        lcd.fillRect(0, 44, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 47, "8. System Setting", false, false, false);
        if(touchUp(Button_OK)){
         guiSystemSetting();

        }
      }
       else {
        lcd_char(1, 2, 47, "8. System Setting", true, false, false);
    }
      } 
    lcd.display();
  } // end bracket while
} // end Function guiMenu()



