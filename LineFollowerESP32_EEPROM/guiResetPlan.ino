void guiResetPlan(){

oledClear();
byte steps = 1;
byte selectPlan = 0;
menuCount = 0;  
while (1) {
  headUp(true, false);
  if (touchUp(Button_RUN)) {
    oledClear();
    break;
  }
  if (steps == 1) {
    sprintf(buff, "P:%d Yakin Dihapus ?", selectPlan + 1);
    lcd_char(1, 0, 15, buff, true, false, false);
    lcd_char(1, 20, 35, "Iya ", true, false, false);
    lcd_char(1, 70, 35, "Tidak", true, false, false);
    if(touchUp(Button_UP)){
      menuCount++;
      if(menuCount > 1) menuCount = 0;
    }
    if(touchUp(Button_DOWN)){
      menuCount--;
      if(menuCount == 255) menuCount = 1;
    }
    if(touchUp(Button_PLUS)){
      if(++selectPlan > 4) selectPlan = 4;
    }
    if(touchUp(Button_MIN)){
      if(--selectPlan == 255) selectPlan = 0;
    }
    if(menuCount == 1){
      lcd.drawRoundRect(18, 33, 22, 12, 2, SH110X_WHITE);
      if(touchUp(Button_OK)) steps = 2;
    } else if(menuCount == 0){
      lcd.drawRoundRect(68, 33, 38, 12, 2, SH110X_WHITE);
      if(touchUp(Button_OK)) break;
    }
  }
  else if (steps == 2) {
    for (byte i = 0; i < VAL_INDEX; i++) {
        idx[selectPlan][i] = 0;
        logic[selectPlan][i] = 0;
        sensLogIdx[selectPlan][i] = 0;
        trigW[selectPlan][i] = 0;
        spdR[selectPlan][i] = 100;
        spdL[selectPlan][i] = 100;
        idelay[selectPlan][i] = 0;
        timerA[selectPlan][i] = 0;
        timerB[selectPlan][i] = 0;
        speedA[selectPlan][i] = 0;
        speedB[selectPlan][i] = 0;
        clrLine[selectPlan][i] = 0;
        pidProfile[selectPlan][i] = 0;
        modeTIM[selectPlan][i] = 0;
      }
    delay(50);
    steps = 3;
  }
  else if (steps == 3) {
    headUp(true, false);
    lcd_char(1, 30, 35, "Selesai!!", true, false, false);
    saveIdxAll();
    lcd.display();
    delay(2000);
    break;
  }
  lcd.display();
} // end bracket while true
}