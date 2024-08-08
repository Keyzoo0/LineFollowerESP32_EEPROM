void TunePid() {
  selectSet = 1;
  selectPresetPID = 0;
  int selectFLMODETest = 0;
  while (1) {
    headUp(true, false);
    if (touchUp(Button_RUN)) {
      maxS = selectSet = 0;
      saveAll();
      delay(50);
      break;
    }
    if (touchUp(Button_DOWN)) {
      selectSet++;
      if (selectSet > 6) selectSet = 1;
    }
    if (touchUp(Button_UP)) {
      selectSet--;
      if (selectSet < 1) selectSet = 6;
    }
    
    if (selectSet == 1) {
      lcd.drawRoundRect(18, 13, 81, 12, 3, SH110X_WHITE);
      if (touchUp(Button_PLUS)) {
        selectPresetPID++;
        if(selectPresetPID > 6) selectPresetPID = 0;
        }
      if (touchUp(Button_MIN)) {
        selectPresetPID--;
        if(selectPresetPID == 255) selectPresetPID = 6;
      }
    }
    if (selectSet == 2) {
      lcd.drawRoundRect(3, 28, 60, 12, 3, SH110X_WHITE);
      if (touchDown(Button_PLUS, 50)) _Kp[selectPresetPID] += 0.1;
      if (touchDown(Button_MIN, 50)) _Kp[selectPresetPID] -= 0.1;
    }
    if (selectSet == 3) {
      lcd.drawRoundRect(63, 28, 60, 12, 3, SH110X_WHITE);
      if (touchDown(Button_PLUS, 50)) _Kd[selectPresetPID] += 0.1;
      if (touchDown(Button_MIN, 50)) _Kd[selectPresetPID] -= 0.1;
    }
    if (selectSet == 4) {
      lcd.drawRoundRect(4, 39, 70, 12, 3, SH110X_WHITE);
      if (touchDown(Button_PLUS, 50)) maxS += 10;
      if (touchDown(Button_MIN, 50)) maxS -= 10;
    }
    if (selectSet == 5){
      lcd.drawRoundRect(74, 39, 50, 12, 3, SH110X_WHITE);
      if (touchUp(Button_PLUS)) {
        selectFLMODETest++;
        if(selectFLMODETest > 2) selectFLMODETest = 0;
      }
      if (touchUp(Button_MIN)) {
        selectFLMODETest--;
        if(selectFLMODETest < 0) selectFLMODETest = 2;
      }
    }
    if (selectSet == 6) {
      lcd.drawRoundRect(30, 50, 56, 12, 3, SH110X_WHITE);
      if (touchUp(Button_OK)) {
        oledClear();
        selectPresetPIDPlay = selectPresetPID;
        while (1) {
          int bufDataSensor = readSensor();
          headUp(true, false);
          dispSensor(bufDataSensor);
          if(selectFLMODETest == 0){
            program(bufDataSensor, "center");
          } else if(selectFLMODETest == 1){
            program(bufDataSensor, "right");
          } else if(selectFLMODETest == 2) {
            program(bufDataSensor, "left");
          }
          if (touchUp(Button_RUN)) {
            oledClear();
            selectSet = 1;
            selectPresetPIDPlay = 0;
            stopMotor();
            break;
          }
          lcd.display();
        }
      }
    }
    lcd_char(1, 20, 15, "Preset:" + (String)slctPID[selectPresetPID], true, false, false);
    lcd_char(1, 5, 30, "Kp: " + String(_Kp[selectPresetPID], 2), true, false, false);
    lcd_char(1, 65, 30, "Kd: " + String(_Kd[selectPresetPID], 2), true, false, false);
    lcd_char(1, 5, 42, "Speed : " + String(maxS), true, false, false);
    lcd_char(1, 76, 42, "FL :" + String(slctFLMODE[selectFLMODETest]), true, false, false);
    lcd_char(1, 33, 53, "Coba PID", true, false, false);
    lcd.display();
  }
}