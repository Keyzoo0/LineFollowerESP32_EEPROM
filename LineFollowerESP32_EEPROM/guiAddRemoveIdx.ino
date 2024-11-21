void addRemoveIdx(byte plan , byte index){
  while (1) {
    if (touchUp(Button_RUN)) {
      oledClear();
      break;
    }

    sprintf(buff ,"Plan-%d | Idx-%2d" , plan+1 , index );
    lcd_char(1 , 20 , 10 , buff , true , true , false);
    if (touchUp(Button_UP)) {
      
      for (byte count = index; count < 99; count++) {
        idx[plan][count+1] = idx[plan][count];
        logic[plan][count+1] = logic[plan][count];
        sensLogIdx[plan][count+1] = sensLogIdx[plan][count];
        spdR[plan][count+1] = spdR[plan][count];
        spdL[plan][count+1] = spdL[plan][count];
        idelay[plan][count+1] = idelay[plan][count];
        timerA[plan][count+1] = timerA[plan][count];
        timerB[plan][count+1] = timerB[plan][count];
        speedA[plan][count+1] = speedA[plan][count];
        speedB[plan][count+1] = speedB[plan][count];
        pidProfile[plan][count+1] = pidProfile[plan][count];
        modeTIM[plan][count+1] = modeTIM[plan][count];
        modeSens[plan][count+1] = modeSens[plan][count];
        usedSens[plan][count+1] = usedSens[plan][count];
      }
        idx[plan][index] = 0;
        logic[plan][index] = 0;
        sensLogIdx[plan][index] = 1;
        spdR[plan][index] = 0;
        spdL[plan][index] = 0;
        idelay[plan][index] = 0;
        timerA[plan][index] = 0;
        timerB[plan][index] = 0;
        speedA[plan][index] = 0;
        speedB[plan][index] = 0;
        pidProfile[plan][index] = 0;
        modeTIM[plan][index] = 0;
        modeSens[plan][index] = 0;  
        usedSens[plan][index] = 0;  
        lcd_char(1 , 50 , 25 , "Added!" , true , true , true );
        saveAll();
        delay(250);
        break;
    
    } else {
      lcd.drawRoundRect(28, 23, 25, 14, 2, SH110X_WHITE);
      lcd_char(1, 31, 26, "Add", true, false, false);
    }

    if (touchUp(Button_PLUS)) {
      for (byte count = index; count < VAL_INDEX; count++) {
        idx[plan][count] = idx[plan][count+1];
        logic[plan][count] = logic[plan][count+1];
        sensLogIdx[plan][count] = sensLogIdx[plan][count+1];
        spdR[plan][count] = spdR[plan][count+1];
        spdL[plan][count] = spdL[plan][count+1];
        idelay[plan][count] = idelay[plan][count+1];
        timerA[plan][count] = timerA[plan][count+1];
        timerB[plan][count] = timerB[plan][count+1];
        speedA[plan][count] = speedA[plan][count+1];
        speedB[plan][count] = speedB[plan][count+1];
        pidProfile[plan][count] = pidProfile[plan][count+1];
        modeTIM[plan][count] = modeTIM[plan][count+1];
        modeSens[plan][count] = modeSens[plan][count+1];
        usedSens[plan][count] = usedSens[plan][count+1];
      }
        idx[plan][VAL_INDEX-1] = 0;
        logic[plan][VAL_INDEX-1] = 0;
        sensLogIdx[plan][VAL_INDEX-1] = 1;
        spdR[plan][VAL_INDEX-1] = 0;
        spdL[plan][VAL_INDEX-1] = 0;
        idelay[plan][VAL_INDEX-1] = 0;
        timerA[plan][VAL_INDEX-1] = 0;
        timerB[plan][VAL_INDEX-1] = 0;
        speedA[plan][VAL_INDEX-1] = 0;
        speedB[plan][VAL_INDEX-1] = 0;
        pidProfile[plan][VAL_INDEX-1] = 0;
        modeTIM[plan][VAL_INDEX-1] = 0;
        modeSens[plan][VAL_INDEX-1] = 0;
        usedSens[plan][VAL_INDEX-1] = 0;
        lcd_char(1 , 50 , 25 , "Removed!" , true , true , true );
        saveAll();
        delay(250);
        break;
    
    } else {
      lcd.drawRoundRect(60, 23, 42, 14, 2, SH110X_WHITE);
      lcd_char(1, 63, 26, "Remove", true, false, false);
    }
    lcd.display();
  } // end while calib bracket

}
