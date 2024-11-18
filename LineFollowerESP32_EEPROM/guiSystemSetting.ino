

void guiSetting(){
  lcd.clearDisplay();
  byte countSetting = 0;
  while(1){
  if(touchUp(Button_UP)){
   lcd.clearDisplay();
   countSetting--;
   if(countSetting == 255) countSetting = 7;
  }else if(touchUp(Button_DOWN)){
   lcd.clearDisplay();
   countSetting++;
   if(countSetting > 7) countSetting = 0;
  }else if(touchUp(Button_RUN)){
    saveAll();
    lcd.clearDisplay();
    break;
  }

   if(countSetting == 0){
      lcd.drawBitmap(25 , 15U, logoSetDefault, 128, 64, SH110X_WHITE);
      lcd_char(1 , 20 , 5 , "Set Default" , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 3 , 3 , 6 , 2 , SH110X_WHITE );
      if(touchUp(Button_OK)){
        lcd.clearDisplay();
        guiSetDefault();
      };
    
    }

   if(countSetting == 1){

      lcd.drawRoundRect(60, 24, 52, 12, 2, SH110X_WHITE);
      sprintf(buff , "AccTA:%2d" , accelTA );
      lcd_char(1, 62, 26, buff, true, false, false);
      lcd.drawRoundRect(60, 40, 52, 12, 2, SH110X_WHITE);
      sprintf(buff , "AccTB:%2d" , accelTB );
      lcd_char(1, 62 , 42 , buff , true, false, false);
      lcd_char(1 , 5  , 5 , "Set Throttle " , true , false , true);
      lcd.drawBitmap(0 , 15, logoSetTrhottle , 128, 64, SH110X_WHITE);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 9  , 3 , 6 , 2 , SH110X_WHITE );
      
      if(touchUp(Button_OK)){
        lcd.clearDisplay();
        bool step = 0;
         while(1){


          if(touchUp(Button_RUN)){
            lcd.clearDisplay();
            break;
          }
          if(touchUp(Button_UP)){
            lcd.clearDisplay();
            step = !step;
          }
          if(touchUp(Button_DOWN)){
            lcd.clearDisplay();
            step = !step;
          }
 

          if(step == 0){

            if(touchDown(Button_PLUS , 200)){
              lcd.clearDisplay();
              accelTA++;
              if(accelTA > 25) accelTA = 1; 
            }
            if(touchDown(Button_MIN , 200)){
              lcd.clearDisplay();
              accelTA--;
              if(accelTA == 0) accelTA = 25; 
            }

            lcd.fillRoundRect(60, 24, 52, 12, 2, SH110X_WHITE);
            sprintf(buff , "AccTA:%2d" , accelTA );
            lcd_char(1, 62, 26, buff, false, false, false);
          }else{
            lcd.drawRoundRect(60, 24, 52, 12, 2, SH110X_WHITE);
            sprintf(buff , "AccTA:%2d" , accelTA );
            lcd_char(1, 62, 26, buff, true, false, false);
          }

          if(step == 1){

            if(touchDown(Button_PLUS , 200)){
              lcd.clearDisplay();
              accelTB++;
              if(accelTB > 25) accelTB = 1; 
            }
            if(touchDown(Button_MIN , 200)){
              lcd.clearDisplay();
              accelTB--;
              if(accelTB == 0) accelTB = 25; 
            }

            lcd.fillRoundRect(60, 40, 52, 12, 2, SH110X_WHITE);
            sprintf(buff , "AccTB:%2d" , accelTB );
            lcd_char(1, 62 , 42 , buff , false, false, false);
          }else{
            lcd.drawRoundRect(60, 40, 52, 12, 2, SH110X_WHITE);
            sprintf(buff , "AccTB:%2d" , accelTB );
            lcd_char(1, 62 , 42 , buff , true, false, false);
          }

          lcd_char(1 , 5  , 5 , "Set Throttle " , true , false , true);
          lcd.drawBitmap(0 , 15, logoSetTrhottle , 128, 64, SH110X_WHITE);
          lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
          lcd.fillRoundRect(117, 9  , 3 , 6 , 2 , SH110X_WHITE );         
          lcd.display();

         }//end While
      }
    }

   if(countSetting == 2){
      lcd.drawBitmap(10, 12, logoSetGripper, 128, 64, SH110X_WHITE);
      lcd_char(1 , 20 , 5 , "Set Gripper" , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 15 , 3 , 6 , 2 , SH110X_WHITE );
      }

   if(countSetting == 3){
      lcd.drawBitmap(5, 15, logoSetFan, 128, 64, SH110X_WHITE);
      lcd_char(1 , 35 , 5 , "Set Fan" , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 21 , 3 , 6 , 2 , SH110X_WHITE );
      }

   if(countSetting == 4){
      lcd.drawBitmap(0, 10, logoSetEncoder , 128, 64, SH110X_WHITE);
      lcd_char(1 , 20 , 0 , "Set Encoder" , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 27 , 3 , 6 , 2 , SH110X_WHITE );
 
      }

   if(countSetting == 5){

      lcd.drawBitmap(0, 15, logoSetWifi, 128, 64, SH110X_WHITE);
      lcd_char(1 , 15 , 5 , "Wi-Fi" , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 33 , 3 , 6 , 2 , SH110X_WHITE );
      }

   if(countSetting == 6){
      lcd.drawBitmap(0, 0, logoCalibSensor , 128, 64, SH110X_WHITE);
      lcd_char(1 , 15 , 5 , "Mode Robot" , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 39 , 3 , 6 , 2 , SH110X_WHITE );
      }

   if(countSetting == 7){
      lcd.drawBitmap(0, 10, logoUpdateOS, 128, 64, SH110X_WHITE);
      lcd_char(1 , 25 , 5 , "Update OS" , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 45 , 3 , 6 , 2 , SH110X_WHITE );
      }

    lcd.display();
 
  }//end while
  saveAll();
 
}



