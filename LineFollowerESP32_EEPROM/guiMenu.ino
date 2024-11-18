

void guiMenu(){
  lcd.clearDisplay();
  countMenu = 0;
  while(1){
    if(touchUp(Button_UP)){
     lcd.clearDisplay();
     countMenu--;
    if(countMenu == 255) countMenu = 7;
    }else if(touchUp(Button_DOWN)){
     lcd.clearDisplay();
     countMenu++;
    if(countMenu > 7) countMenu = 0;
    }else if(touchUp(Button_RUN)){
     lcd.clearDisplay();
     break;
    }

   if(countMenu == 0){
      if(touchUp(Button_PLUS)){
        plan++;
        if(plan >= VAL_PLAN) plan = 0 ;
      lcd.clearDisplay();
    
      }else if(touchUp(Button_MIN)){
        plan--;
        if(plan == 255) plan = VAL_PLAN-1 ;
        lcd.clearDisplay();
      } else if(touchUp(Button_OK)){
        setIDX();
      }
      lcd.drawBitmap(0, 5, logoSetPlan, 128, 64, SH110X_WHITE);
      lcd_char(3 , 75 , 25 , "P"+String(plan+1) , true , false , true);
      lcd_char(1 , 40 , 5 , "Set Plan" , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 3 , 3 , 6 , 2 , SH110X_WHITE );
      }

   if(countMenu == 1){
      if(touchUp(Button_PLUS)) calibAuto();
      else if(touchUp(Button_MIN)) calibManual();
      
      lcd.drawRoundRect(65, 25, 27, 11, 2, SH110X_WHITE);
      lcd_char(1, 67, 26, "Auto", true, false, false);
      lcd.drawRoundRect(65, 40, 40, 12, 2, SH110X_WHITE);
      lcd_char(1, 67 , 42 , "Manual", true, false, false);
      lcd_char(1 , 15 , 5 , "Calib Sensor" , true , false , true);
      lcd.drawBitmap(0, 5, logoCalibSensor, 128, 64, SH110X_WHITE);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 9  , 3 , 6 , 2 , SH110X_WHITE );
      }

   if(countMenu == 2){
      if(touchUp(Button_OK)) guiTunePid();
      lcd.drawBitmap(0, 0, logoTunePID, 128, 64, SH110X_WHITE);
      lcd_char(1 , 15 , 5 , "Tuning PID" , true , false , true);

      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 15 , 3 , 6 , 2 , SH110X_WHITE );
      }

   if(countMenu == 3){
      if(touchUp(Button_OK)) guiTestMotor();
      lcd.drawBitmap(0, 0, logoTestMotor, 128, 64, SH110X_WHITE);
      lcd_char(1 , 15 , 5 , "Test Motor" , true , false , true);

      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 21 , 3 , 6 , 2 , SH110X_WHITE );
      }

   if(countMenu == 4){
      if(touchUp(Button_OK)) CMIDX();
      lcd.drawBitmap(0, 0, logoCopyMirrorPlan, 128, 64, SH110X_WHITE);
      lcd_char(1 , 15 , 5 , "Copy Mirror Plan" , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 27 , 3 , 6 , 2 , SH110X_WHITE );
      lcd.drawRoundRect(65, 24, 40 , 12, 2, SH110X_WHITE);
      lcd_char(1, 67, 26, " Copy " , true, false, false);
      lcd.drawRoundRect(62, 40,  16 , 12, 2, SH110X_WHITE);     
      sprintf(buff , "P%d" , 1);
      lcd_char(1, 65, 42, buff , true, false, false);
      lcd.drawRoundRect(90, 40,  16 , 12, 2, SH110X_WHITE);
      sprintf(buff , "P%d" , 1);
      lcd_char(1, 93, 42, buff , true, false, false);
      lcd_char(1, 82, 42, ">" , true, false, false);
      }

   if(countMenu == 5){
     if(touchUp(Button_PLUS)){
        plan++;
        if(plan >= VAL_PLAN) plan = 0 ;
      lcd.clearDisplay();
    
      }else if(touchUp(Button_MIN)){
        plan--;
        if(plan == 255) plan = VAL_PLAN-1 ;
        lcd.clearDisplay();
      }
      if(touchUp(Button_OK)){
        guiResetPlan(plan);
      } 

      lcd.drawBitmap(0, 0, logoDeletePlan, 128, 64, SH110X_WHITE);
      lcd_char(1 , 15 , 5 , "Delete Plan" , true , false , true);
      lcd_char(3 , 75 , 25 , "P"+String(plan+1) , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 33 , 3 , 6 , 2 , SH110X_WHITE );
      }

   if(countMenu == 6){
      lcd.drawBitmap(0, 0, logoTransferPlan, 128, 64, SH110X_WHITE);
      lcd_char(1 , 15 , 5 , "Transfer Plan" , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 39 , 3 , 6 , 2 , SH110X_WHITE );
      }

   if(countMenu == 7){
      if(touchUp(Button_OK))  guiSetting();

      lcd.drawBitmap(0, 0, logoSettings, 128, 64, SH110X_WHITE);
      lcd_char(1 , 25 , 5 , "Settings" , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 45 , 3 , 6 , 2 , SH110X_WHITE );
      }

    lcd.display();
 
  }//end while
  saveAll();
  delay(10);

}



