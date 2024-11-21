
void guiHome() {
  stopMotor();
  initEncoder(false);
  while (1) {
home:
    headUp(true, false);
    displaySensor(readSensor());
    if (touchUp(btnUp)) {
      menuHome++;
      if (menuHome > 4) menuHome = 0;
    }
    if (touchUp(btnDown)) {
      menuHome--;
      if (menuHome == 255) menuHome = 4;
    }

    if (menuHome == 0) {
      lcd.fillRoundRect(48, 30 , 30, 30, 5, SH110X_WHITE);
      if (touchUp(btnPlus)) mode = true;
      if (touchUp(btnMinus)) mode = false;
      if (mode){
        if(touchUp(btnOk)){
          lcd.clearDisplay();
          guiMenu();
        }  
        lcd_char(3, 56, 35, "C", false, false, false);
      }
      else {
        if(touchUp(btnOk)){
          lcd.clearDisplay();
          guiMenu();
        }
        lcd_char(3, 56, 35, "F", false, false, false);
      }
    } else {
      lcd.drawRoundRect(48, 30 , 30, 30, 5, SH110X_WHITE);
      if (mode)lcd_char(3, 56, 35, "C", true, false, false);
      else {
        lcd_char(3, 56, 35, "F", true, false, false);
      }
    }
    if (menuHome == 1) {
      if (touchDown(btnOk,50)) {
        setIDX();
      }
      if (touchDown(btnPlus,50)) {

        plan++;
        if (plan >= VAL_PLAN) plan = 0;

        saveHome();
      }
      if (touchUp(btnMinus)) {

        plan--;
        if (plan == 255) plan = VAL_PLAN-1;
        saveHome();
      }
      lcd.fillRoundRect(-5, 27, 45, 20, 3, SH110X_WHITE);
      sprintf(buff, "SetP:%d", plan + 1);
      lcd_char(1, 1, 31, buff, false, false, false);
    } else {
      lcd.drawRoundRect(-5, 27, 45, 20, 3, SH110X_WHITE);
      sprintf(buff, "SetP:%d", plan + 1);
      lcd_char(1, 1, 31, buff, true, false, false);
    }
    if (menuHome == 2) {
      if (touchDown(btnPlus,50)) {
        normalSpeed = normalSpeed + 5;
        if (normalSpeed == 4) normalSpeed = 0;
        delay(100);
        saveHome();
      }
      if (touchDown(btnMinus,50)) {
        normalSpeed = normalSpeed - 5;
        if (normalSpeed > 250) normalSpeed = 255;
        delay(100);
        saveHome();
      }
      lcd.fillRoundRect(-5, 42, 45, 20, 3, SH110X_WHITE);
      sprintf(buff, "Ns:%03d", normalSpeed);
      lcd_char(1, 1, 51, buff, false, false, false);
    } else {
      lcd.drawRoundRect(-5, 42, 45, 20, 3, SH110X_WHITE);
      sprintf(buff, "Ns:%03d", normalSpeed);
      lcd_char(1, 1, 51, buff, true, false, false);
    }
    if (menuHome == 3) {
      if (touchUp(btnOk)) {
        saveHome();
        menuCheckpoint();
      }
      lcd.fillRoundRect(87, 42, 45, 20, 3, SH110X_WHITE);
      lcd_char(1, 90, 51, "CHKPNT", false, false, false);
    } else {
      lcd.drawRoundRect(87, 42, 45, 20, 3, SH110X_WHITE);
      lcd_char(1, 90, 51, "CHKPNT", true, false, false);
    }
    if (menuHome == 4) {
      if (touchUp(btnOk)) {
        guiCalSensor();
      }
      lcd.fillRoundRect(87, 27, 45, 20, 3, SH110X_WHITE);
      sprintf(buff, "CALSEN");
      lcd_char(1, 90, 31, buff, false, false, false);
    } else {
      lcd.drawRoundRect(87, 27, 45, 20, 3, SH110X_WHITE);
      sprintf(buff, "CALSEN");
      lcd_char(1, 90, 31, buff, true, false, false);
    }
    lcd.display();

    if (touchUp(btnBack)) {
      saveHome();
      break;
    }
  }
  if (readBattery() < minBat) {
    headUp(true, false);
    lcd_char(2, 25, 15, "BATTERY", true, false, false);
    lcd_char(2, 48, 35, "LOW", true, false, true);
    delay(1500);
    goto home;
  }

  if (mode) {
    chkPnt();
    lcd.clearDisplay();
    lcd.drawBitmap(0, -5, Logo_EEPROM, 128, 64, SH110X_WHITE);
    lcd_char(1, 46, 56, "EEPROM", true, false, true);
    sw_millis.start();
    int dataSensor;
    int setSensor;
    int timerSpeedA = 0, timerSpeedB = 0;
    long TA = 0, TB = 0;
    if (protec) {
      TA = iDelayCheckpoint[plan][slct];
      timerSpeedA = normalSpeed;
      long lastmsg = millis();
      int speedThrottle = timerSpeedA / 4;
      while (1) {
        if (speedThrottle < normalSpeed) {
          speedThrottle += 2;
          maxS = speedThrottle;
          if (speedThrottle >= normalSpeed) maxS = normalSpeed;
        }
        dataSensor = readSensor();
        program(dataSensor , modeSens[plan][start] , maxS , pidProfile[plan][start] , usedSens[plan][start]);

        if (touchUp(btnOk)) {
          sw_millis.stop();
          stopMotor();
          goto lastStop;
          break;
        }

        if ((millis()  - lastmsg) >= TA) break;
      }

      timerSpeedA = 0;
      timerSpeedB = 0;
      TA = 0;
      TB = 0;

      if (start == stopCount) {
        sw_millis.stop();
        stopMotor();
        goto lastStop;
      } else start = readIdxCheckpoint[plan][slct]+1;
    }

    while (1) {
      long lastmsgA;
      long lastmsgB;
      bool do_action = false;

      dataSensor = readSensor();
      setSensor = sensLog[sensLogIdx[plan][start]];

      if (logic[plan][start] == 0) { //OR
       
          if (dataSensor & setSensor) {
            do_action = true;
          }
          else {
            program(dataSensor , modeSens[plan][start] , normalSpeed , pidProfile[plan][start] , usedSens[plan][start]);
            do_action = false;
          }
        
      }
      else if (logic[plan][start] == 1) { //AND
        if ((dataSensor & setSensor) == setSensor) do_action = true;
        else {
            program(dataSensor , modeSens[plan][start] , normalSpeed , pidProfile[plan][start] , usedSens[plan][start]);
          do_action = false;
        }
      } else if (logic[plan][start] == 2) { //TIM
        do_action = true;
      } else if (logic[plan][start] == 3) { //XOR
        
      }

      if (do_action) {
        read_counter();
        dataSensor = readSensor();

        
        TA = timerA[plan][start] ;
        lastmsgA = millis();
     
        timerSpeedA = speedA[plan][start];
        int speedThrottleA = timerSpeedA / 4;
        while (1) {
          if (speedThrottleA < speedA[plan][start]) {
            speedThrottleA += 2;
            if (speedThrottleA < 50) maxS = 50;
            else maxS = speedThrottleA;
            if (speedThrottleA >= speedA[plan][start]) maxS = speedA[plan][start];
          }
          dataSensor = readSensor();
          program(dataSensor , modeSens[plan][start] , maxS , pidProfile[plan][start] , usedSens[plan][start]);
        if (touchUp(btnOk)) {
        sw_millis.stop();
        stopMotor();
        TA = 0;
        TB = 0;
        break;
      }
          if (TA > 0) {
              if ((millis()  - lastmsgA) > TA * 15) break;
          } else break;
        }

        
        TB = timerB[plan][start];
        lastmsgB = millis();
        
        timerSpeedB = speedB[plan][start];
        int speedThrottleB = timerSpeedB / 4;
        int SpeedAB = Plan[plan].savespeedA[start];
        while (1) {
          if (TA == 0) {
            speedThrottleB += 2;
            if (speedThrottleB < 50) maxS = 50;
            else maxS = speedThrottleB;
            if (speedThrottleB >= speedB[plan][start]) maxS = speedB[plan][start];
          } else if (speedB[plan][start] > speedA[plan][start]) {
            SpeedAB += 2;
            maxS = SpeedAB;
            if (SpeedAB >= speedB[plan][start]) maxS = speedB[plan][start];
          } else if (speedB[plan][start] < speedA[plan][start]) {
            SpeedAB -= 2;
            maxS = SpeedAB;
            if (SpeedAB <= speedB[plan][start]) maxS = speedB[plan][start];
          }
          dataSensor = readSensor();
          program(dataSensor , modeSens[plan][start] , maxS , pidProfile[plan][start] , usedSens[plan][start]);

        if (touchUp(btnOk)) {
        sw_millis.stop();
        stopMotor();
        TA = 0;
        TB = 0;
        break;
      }
          if (TB > 0) {
              if ((millis()  - lastmsgB) > TB * 15) break;
          } else break;
        }

        TA = 0;
        TB = 0;

        if (start >= stopCount) {
          sw_millis.stop();
          stopMotor();
          TA = 0;
          TB = 0;
          break;
        }
        start ++;
        do_action = false;
      }

      if (touchUp(btnOk)) {
        sw_millis.stop();
        stopMotor();
        TA = 0;
        TB = 0;
        break;
      }
    }
lastStop:
    while (1) {
      headUp(true, false);
      stopMotor();
      double detik;
      detik = sw_millis.elapsed() * 0.001;
      sprintf(buff, "Stop : %d", start);
      lcd_char(1, 5, 17, buff, true, false, false);
      sprintf(buff, "TIME : %.3f Second", detik);
      lcd_char(1, 5, 30, buff, true, false, false);
      lcd_char(1, 5, 45, "Press Button", true, false, false);
      lcd_char(1, 5, 55, "OKE To Relase", true, false, true);
      if (touchUp(btnOk)) {
        stopMotor();
        sw_millis.reset();
        menuHome = 0;
        break;
      }
    }
  }
  else {
    guiTunePid();
  }
}
