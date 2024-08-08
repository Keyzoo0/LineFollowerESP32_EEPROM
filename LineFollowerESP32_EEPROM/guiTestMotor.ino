void guiTestMotor(){
oledClear();
byte steps = 0;
byte speedsR = 0;
byte speedsL = 0;
char Sdirection[3][3] = {"F", "B" , "S" };
byte selectDirectR = 0;
byte selectDirectL = 0;
menuCount = 0;
initEncoder(true);
while (1) {
  headUp(true, false);
  if (touchUp(Button_RUN)) {
    speedsR = speedsL = 0;
    pwmMotor(0, 0);
    stopMotor();
    initEncoder(false);
    break;
  }
  if (touchUp(Button_OK)) {
    menuCount++;
    if (menuCount > 2) menuCount = 1;
  }

  if (menuCount == 1) {
    if (touchUp(Button_DOWN)) {
      steps++;
      if (steps > 2) steps = 0;
    }else if (touchUp(Button_UP)) {
      steps--;
      if (steps < 0) steps = 2;
    }
    if (steps == 1) {
      lcd_char(1, 65, 30, ">", true, false, false);
      if (touchUp(Button_PLUS )) {
        selectDirectR++;
        if (selectDirectR > 2) selectDirectR = 0;
      }
      if (touchUp(Button_MIN)) {
        selectDirectR--;
        if (selectDirectR == 255) selectDirectR == 2;
      }
    }
    else if (steps == 2) {
      lcd_char(1, 65, 40, ">", true, false, false);
      if (touchDown(Button_PLUS , 50)) {
        speedsR+=5;
        if (speedsR > 255) speedsR = 255;
      }
      if (touchDown(Button_MIN , 50)) {
        speedsR-=5;
        if (speedsR < 0) speedsR == 255;
      }
    }
    sprintf(buff, "Direct: %s", Sdirection[selectDirectR]);
    lcd_char(1, 70, 30, buff, true, false, false);
    lcd_char(1, 70, 40, "Speed:" + String(speedsR), true, false, false);
    lcd_char(1, 70, 50, "RPM: " + String(rpmR), true, false, false);
    lcd.fillRoundRect(65, 15, 60, 12, 2, SH110X_WHITE);
    lcd_char(1, 67, 17, "MTR Kanan", false, false, false);
  } else {
      sprintf(buff, "Direct: %s", Sdirection[selectDirectR]);
      lcd_char(1, 70, 30, buff, true, false, false);
      lcd_char(1, 70, 40, "Speed:" + String(speedsR), true, false, false);
      lcd_char(1, 70, 50, "RPM: " + String(rpmR), true, false, false);
      lcd.drawRoundRect(65, 15, 60, 12, 2, SH110X_WHITE);
      lcd_char(1, 67, 17, "MTR Kanan", true, false, false);
  }

  if (menuCount == 2) {
    if (touchUp(Button_DOWN)) {
      steps++;
      if (steps > 2) steps = 1;
    }else if (touchUp(Button_UP)) {
      steps--;
      if (steps < 1) steps = 2;
    }
       if (steps == 1) {
      lcd_char(1, 0, 30, ">", true, false, false);
      if (touchUp(Button_PLUS)) {
        selectDirectL++;
        if (selectDirectL > 2) selectDirectL = 0;
      }
      if (touchUp(Button_MIN)) {
        selectDirectL--;
        if (selectDirectL == 255) selectDirectL == 2;
      }
    }
    else if (steps == 2) {
      lcd_char(1, 0, 40, ">", true, false, false);
      if (touchDown(Button_PLUS , 50)) {
        speedsL+=5;
        if (speedsL > 255) speedsL = 255;
      }
      if (touchDown(Button_MIN , 50)) {
        speedsL-=5;
        if (speedsL < 0) speedsL == 255;
      }
    }
    sprintf(buff, "Direct: %s", Sdirection[selectDirectL]);
    lcd_char(1, 5, 30, buff, true, false, false);
    lcd_char(1, 5, 40, "Speed:" + String(speedsL), true, false, false);
    lcd_char(1, 5, 50, "RPM: " + String(rpmL), true, false, false);
    lcd.fillRoundRect(0, 15, 60, 12, 2, SH110X_WHITE);
    lcd_char(1, 2, 17, "MTR Kiri", false, false, false);
  } else {
    sprintf(buff, "Direct: %s", Sdirection[selectDirectL]);
    lcd_char(1, 5, 30, buff, true, false, false);
    lcd_char(1, 5, 40, "Speed:" + String(speedsL), true, false, false);
    lcd_char(1, 5, 50, "RPM: " + String(rpmL), true, false, false);
    lcd.drawRoundRect(0, 15, 60, 12, 2, SH110X_WHITE);
    lcd_char(1, 2, 17, "MTR Kiri", true, false, false);
  }
  pwmMotor(selectDirectL == 0 ? speedsL : speedsL * -1, selectDirectR == 0 ? speedsR : speedsR * -1);
  if(selectDirectL == 2)stopMotorL();
  if(selectDirectR == 2)stopMotorR();
  
//            pwmMotor(selectDirectL == 0 ? map2(speedsL, 0, 100, 0, 255) : map2(speedsL, 0, 100, 0, 255) * -1,  selectDirectR == 0 ? map2(speedsR, 0, 100, 0, 255) : map2(speedsR, 0, 100, 0, 255) * -1);
  lcd.display();
  }
}
