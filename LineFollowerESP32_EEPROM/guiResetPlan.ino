void guiResetPlan(byte selectPlan){

oledClear();
byte steps = 1;
menuCount = 0;  
while (1) {
  headUp(true, false);
  if (touchUp(Button_RUN)) {
    oledClear();
    break;
  }
  if (steps == 1) {
    sprintf(buff, " Yakin menghapus P%d ?", selectPlan + 1);
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
   
    if(menuCount == 1){
      lcd.drawRoundRect(18, 33, 22, 12, 2, SH110X_WHITE);
      if(touchUp(Button_OK)) steps = 2;
    } else if(menuCount == 0){
      lcd.drawRoundRect(68, 33, 38, 12, 2, SH110X_WHITE);
      if(touchUp(Button_OK)) {
        lcd.clearDisplay();
        break;
      }
    }
  }
  else if (steps == 2) {
     for (byte i = 0; i < VAL_INDEX; i++) {
        idx[selectPlan][i] = 0;
        logic[selectPlan][i] = 0;
        sensLogIdx[selectPlan][i] = 1;
        spdR[selectPlan][i] = 80;
        spdL[selectPlan][i] = 80;
        idelay[selectPlan][i] = 50;
        timerA[selectPlan][i] = 0;
        timerB[selectPlan][i] = 0;
        speedA[selectPlan][i] = 80;
        speedB[selectPlan][i] = 80;
        pidProfile[selectPlan][i] = 3;
        modeTIM[selectPlan][i] = 0;
        modeSens[selectPlan][i] = 0;
        usedSens[selectPlan][i] = 0;
                
      }

    delay(50);
    steps = 3;
  }
  else if (steps == 3) {
    headUp(true, false);
    sprintf(buff , "P%d Terhapus!!" , selectPlan+1);
    lcd_char(1, 20 , 35, buff , true, false, false);
    saveAll();
    lcd.display();
    delay(2000);
    lcd.clearDisplay();
    break;
  }
  lcd.display();
} // end bracket while true
}