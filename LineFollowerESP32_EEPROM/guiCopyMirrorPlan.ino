
void CMIDX() {
  const char* mode []= { " Copy " , "Mirror"};
  char modCopy[2][7] = {"COPY", "MIRROR"};
  byte x1, x2;
  bool selectModeCM = 0;
  byte steps = 1;
  bool doneCM = false;
  selectSet = 0;
  while (1) {
    
      lcd.drawBitmap(0, 0, logoCopyMirrorPlan, 128, 64, SH110X_WHITE);
      lcd_char(1 , 15 , 5 , "Copy Mirror Plan" , true , false , true);
      lcd.fillRoundRect(118 , 0 , 1 , 55 , 0 , SH110X_WHITE );
      lcd.fillRoundRect(117, 27 , 3 , 6 , 2 , SH110X_WHITE );

     if(touchUp(Button_RUN)){
      byte selectModeCM = 0;
      lcd.clearDisplay();
      break;
     }

    if(touchUp(Button_UP)){
      lcd.clearDisplay();
      steps++;
      if(steps > 3 ) steps = 1;
    }

    if(touchUp(Button_DOWN)){
      lcd.clearDisplay();
      steps--;
      if(steps < 1 ) steps = 3;
    }


    if(touchUp(Button_OK)){
      lcd.clearDisplay();
      steps = 5;
    }

    
     //mode
    if(steps == 1){
     if(touchUp(Button_PLUS)){
       lcd.clearDisplay();
       selectModeCM = !selectModeCM;
     }
     if(touchUp(Button_MIN)){
       lcd.clearDisplay();
       selectModeCM = !selectModeCM;
     }
     lcd.fillRoundRect(65, 24, 40 , 12, 2, SH110X_WHITE);
     lcd_char(1, 67, 26, mode[selectModeCM] , false, false, false);
    }else{
     lcd.drawRoundRect(65, 24, 40 , 12, 2, SH110X_WHITE);
     lcd_char(1, 67, 26, mode[selectModeCM] , true, false, false);
    }
     
     //x1
    if(steps == 2){
      if(touchUp(Button_PLUS)){
         lcd.clearDisplay();
         x1++ ;
         if(x1 >= VAL_PLAN ) x1 = 0 ;
       }
      if(touchUp(Button_MIN)){
         lcd.clearDisplay();
         x1-- ;
         if(x1 == 255 ) x1 = VAL_PLAN-1 ;
       }

     lcd.fillRoundRect(62, 40,  16 , 12, 2, SH110X_WHITE);     
     sprintf(buff , "P%d" , x1+1);
     lcd_char(1, 65, 42, buff , false, false, false);
    }else{
     lcd.drawRoundRect(62, 40,  16 , 12, 2, SH110X_WHITE);     
     sprintf(buff , "P%d" , x1+1);
     lcd_char(1, 65, 42, buff , true, false, false);
    }


    //x2
    if(steps == 3){
    
      if(touchUp(Button_PLUS)){
         lcd.clearDisplay();
         x2++ ;
         if(x2 >= VAL_PLAN ) x2 = 0 ;
       }
      if(touchUp(Button_MIN)){
         lcd.clearDisplay();
         x2-- ;
         if(x2 == 255 ) x2 = VAL_PLAN-1 ;
       }
 
     lcd.fillRoundRect(90, 40,  16 , 12, 2, SH110X_WHITE);
     sprintf(buff , "P%d" , x2+1);
     lcd_char(1, 93, 42, buff , false, false, false);
    }else{
     lcd.drawRoundRect(90, 40,  16 , 12, 2, SH110X_WHITE);
     sprintf(buff , "P%d" , x2+1);
     lcd_char(1, 93, 42, buff , true, false, false);
    }

     lcd_char(1, 82, 42, ">" , true, false, false);

     
     // selectModeCM
     // x1 
     // x2 
 
    if (steps == 5) {
        if (x1 == x2) {
          lcd_char(1, 10, 20, "Invalid Same Plan!", true, true, true);
          delay(2000);
          oledClear();
          steps=1;
        } else {
          oledClear();
          steps = 1;

      if (selectModeCM == 0) { // Mode Normal
        oledClear();
        for (byte i = 0; i < 100; i++) {
          idx[x2][i] = idx[x1][i];
          logic[x2][i] = logic[x1][i];
          sensLogIdx[x2][i] = sensLogIdx[x1][i];
          spdR[x2][i] = spdR[x1][i];
          spdL[x2][i] = spdL[x1][i];
          idelay[x2][i] = idelay[x1][i];
          timerA[x2][i] = timerA[x1][i];
          timerB[x2][i] = timerB[x1][i];
          speedA[x2][i] = speedA[x1][i];
          speedB[x2][i] = speedB[x1][i];
          pidProfile[x2][i] = pidProfile[x1][i];
          modeTIM[x2][i] = modeTIM[x1][i];
          modeSens[x2][i] = modeSens[x1][i];
          usedSens[x2][i] = usedSens[x1][i];

          lcd_loading(5,  29 , i, true, false, false);
          lcd.display();
          delay(25);
          if (i == 99) {
            doneCM = true;
          }
        }
      } // end select mode 0 CM
      else if (selectModeCM == 1) { // Mode Mirror
        oledClear();
        for (byte i = 0; i < 100; i++) {
          if(idx[x1][i] == 2) idx[x2][i] = 3;
          else if (idx[x1][i] == 3) idx[x2][i] = 2;
          else if (idx[x1][i] == 7) idx[x2][i] = 8;
          else if (idx[x1][i] == 8) idx[x2][i] = 7;
          else idx[x2][i] = idx[x1][i];
          
          logic[x2][i] = logic[x1][i];
          if (sensLogIdx[x1][i] == 2) sensLogIdx[x2][i] = 3;
          else if (sensLogIdx[x1][i] == 4) sensLogIdx[x2][i] = 5;
          else if (sensLogIdx[x1][i] == 6) sensLogIdx[x2][i] = 7;
          else if (sensLogIdx[x1][i] == 8) sensLogIdx[x2][i] = 9;
          else if (sensLogIdx[x1][i] == 10) sensLogIdx[x2][i] = 11;
          else if (sensLogIdx[x1][i] == 12) sensLogIdx[x2][i] = 13;
          else if (sensLogIdx[x1][i] == 16) sensLogIdx[x2][i] = 17;
          else if (sensLogIdx[x1][i] == 18) sensLogIdx[x2][i] = 19;
          else if (sensLogIdx[x1][i] == 3) sensLogIdx[x2][i] = 2;
          else if (sensLogIdx[x1][i] == 5) sensLogIdx[x2][i] = 4;
          else if (sensLogIdx[x1][i] == 7) sensLogIdx[x2][i] = 6;
          else if (sensLogIdx[x1][i] == 9) sensLogIdx[x2][i] = 8;
          else if (sensLogIdx[x1][i] == 11) sensLogIdx[x2][i] = 10;
          else if (sensLogIdx[x1][i] == 13) sensLogIdx[x2][i] = 12;
          else if (sensLogIdx[x1][i] == 17) sensLogIdx[x2][i] = 16;
          else if (sensLogIdx[x1][i] == 19) sensLogIdx[x2][i] = 18;
          else sensLogIdx[x2][i] = sensLogIdx[x1][i];
          

          spdR[x2][i] = spdR[x1][i];
          spdL[x2][i] = spdL[x1][i];
          idelay[x2][i] = idelay[x1][i];
          timerA[x2][i] = timerA[x1][i];
          timerB[x2][i] = timerB[x1][i];
          speedA[x2][i] = speedA[x1][i];
          speedB[x2][i] = speedB[x1][i];
          pidProfile[x2][i] = pidProfile[x1][i];
          modeTIM[x2][i] = modeTIM[x1][i];
          usedSens[x2][i] = usedSens[x1][i];
          
          if(modeSens[x1][i] == 2 ) modeSens[x2][i] = 1;
          else if(modeSens[x1][i] == 1 ) modeSens[x2][i] = 2;
          else modeSens[x2][i] = modeSens[x1][i] ;

          

          lcd_loading(1, 29, i, true, false, false);
          lcd.display();
          delay(10);
          if (i == 99) {
            saveAll();
            doneCM = true;
           }
         }
        } // end select mode 1 CM
      }
    }
    if(doneCM){
      oledClear();
      lcd_char(1, 25, 10, "Plan " + String(x1 + 1) + " telah " , true, false, false);
      lcd_char(1, 5, 25, "ter" + String(mode[selectModeCM]) + " di Plan " + String(x2 + 1)  , true, false, false);
      lcd.display();
      delay(3000);
      oledClear();
      break;
    }
    lcd.display();
  }
}
