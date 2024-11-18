
void guiSetDefault(){
 
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
    sprintf(buff, "Set Default Robot?");
    lcd_char(1, 15, 15, buff, true, false, false);
    lcd_char(1, 20, 35, "Yes", true, false, false);
    lcd_char(1, 70, 35, "Cancel", true, false, false);
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
    for(int selectPlan = 0 ; selectPlan < VAL_PLAN ; selectPlan++ ){
    // reset home 
    plan = 0;
    normalSpeed = 120;
    stopIndex = 0;
    countCP = 0;  
    //reset all index at all plan
      for (byte i = 0; i < VAL_INDEX; i++) {
        idx[selectPlan][i] = 0;
        logic[selectPlan][i] = 0;
        sensLogIdx[selectPlan][i] = 1;
        trigW[selectPlan][i] = 1;
        spdR[selectPlan][i] = 80;
        spdL[selectPlan][i] = 80;
        idelay[selectPlan][i] = 0;
        timerA[selectPlan][i] = 0;
        timerB[selectPlan][i] = 0;
        speedA[selectPlan][i] = 100;
        speedB[selectPlan][i] = 100;
        clrLine[selectPlan][i] = 0;
        pidProfile[selectPlan][i] = 3;
        modeTIM[selectPlan][i] = 0;
        modeSens[selectPlan][i] = 0;

      }

       for (byte i = 0; i < VAL_CHECKP; i++) {
         readCCheckpoint[selectPlan][i] = 0;
         iDelayCheckpoint[selectPlan][i] = 0;
         timerACheckpoint[selectPlan][i] = 0;
         readIdxCheckpoint[selectPlan][i] = 0; 
       }
    
    }    
     
     
    delay(50);
    steps = 3;
  }
  else if (steps == 3) {
    headUp(true, false);
    lcd_char(1, 35, 35, "Selesai!!", true, false, false);
    saveAll();
    lcd.display();
    delay(1000);
    lcd.clearDisplay(); 
    break;
  }
  lcd.display();
  }
}
