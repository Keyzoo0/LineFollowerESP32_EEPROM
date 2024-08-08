
void menuCheckpoint(){
  while(1){
          headUp(true, false);
          if(touchUp(Button_RUN)){
            oledClear();
            saveCP();
            break;
          }
          if(touchUp(Button_UP)){
            selectSet++;
            if(selectSet > 3) selectSet = 3;
          }
          if(touchUp(Button_DOWN)){
            selectSet--;
            if(selectSet == 255) selectSet = 0; 
          }

          if(selectSet == 0){
            lcd_char(1, 0, 15, ">", true, false, false);
            if(touchUp(Button_PLUS)){
              readCCheckpoint[plan][countCP]++;
              if(readCCheckpoint[plan][countCP] > 3) readCCheckpoint[plan][countCP] = 0;
            }
            if(touchUp(Button_MIN)){
              readCCheckpoint[plan][countCP]--;
              if(readCCheckpoint[plan][countCP] == 255) readCCheckpoint[plan][countCP] = 3;
            }
          } else if(selectSet == 1){
            lcd_char(1, 0, 25, ">", true, false, false);
            if(touchUp(Button_PLUS)){
              iDelayCheckpoint[plan][countCP]++;
            }
            if(touchUp(Button_MIN)){
              iDelayCheckpoint[plan][countCP]--;
            }
          } else if(selectSet == 2){
            lcd_char(1, 0, 35, ">", true, false, false);
            if(touchUp(Button_PLUS)){
              timerACheckpoint[plan][countCP]++;
            }
            if(touchUp(Button_MIN)){
              timerACheckpoint[plan][countCP]--;
            }
          } else if(selectSet == 3){
            lcd_char(1, 0, 45, ">", true, false, false);
            if(touchUp(Button_PLUS)){
              readIdxCheckpoint[plan][countCP]++;
              if(readIdxCheckpoint[plan][countCP] > 100) readIdxCheckpoint[plan][countCP] = 100;
            }
            if(touchUp(Button_MIN)){
              readIdxCheckpoint[plan][countCP]--;
              if(readIdxCheckpoint[plan][countCP] == 255) readIdxCheckpoint[plan][countCP] = 0;
            }
          }
          
          lcd.drawRoundRect(32, 0, 23, 10, 3, SH110X_WHITE);
          sprintf(buff, "P:%d", plan + 1);
          lcd_char(1, 36, 2, buff, true, false, false);
          
          lcd_char(1, 10, 15, "ACTION: " + String(actCheckpoint[readCCheckpoint[plan][countCP]]), true, false, false);
          lcd_char(1, 10, 25, "D ACT : " + String(iDelayCheckpoint[plan][countCP]) + " mS", true, false, false);
          lcd_char(1, 10, 35, "SET SA: " + String(timerACheckpoint[plan][countCP]) + " mS" , true, false, false);
          lcd_char(1, 10, 45, "READIX: " + String(readIdxCheckpoint[plan][countCP]), true, false, false);
          lcd.display();
        }
}