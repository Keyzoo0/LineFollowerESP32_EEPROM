
void menuCheckpoint(){
  while(1){
          lcd.clearDisplay();
          if(touchUp(Button_RUN)){
            oledClear();
            saveAll();
            break;
          }
          if(touchUp(Button_DOWN)){
            selectSet++;
            if(selectSet > 4) selectSet = 0;
          }
          if(touchUp(Button_UP)){
            selectSet--;
            if(selectSet == 255) selectSet = 4; 
          }
          if(selectSet == 0){
            lcd_char(1, 0, 5, ">", true, false, false);
            if(touchUp(Button_PLUS)){
              countCP++;
              if( countCP >= VAL_CHECKP ) countCP = 0;
            }
            if(touchUp(Button_MIN)){
              countCP--;
              if( countCP == 255 ) countCP = VAL_CHECKP-1;
            }
          } else if(selectSet == 1){
            lcd_char(1, 0, 15, ">", true, false, false);
            if(touchDown(Button_PLUS,75)){
              CP[plan].saveAct[countCP]++;
              if(CP[plan].saveAct[countCP] > 3) CP[plan].saveAct[countCP]= 0;
            }
            if(touchDown(Button_MIN,75)){
              CP[plan].saveAct[countCP]--;
              if(CP[plan].saveAct[countCP] == 255) CP[plan].saveAct[countCP] = 3;
            }
          } else if(selectSet == 2){
            lcd_char(1, 0, 25, ">", true, false, false);
            if(touchDown(Button_PLUS,75)){
              CP[plan].saveiDelay[countCP]++;
            }
            if(touchDown(Button_MIN,75)){
              CP[plan].saveiDelay[countCP]--;
            }
          } else if(selectSet == 3){
            lcd_char(1, 0, 35, ">", true, false, false);
            if(touchDown(Button_PLUS,75)){
              CP[plan].savetimerA[countCP]++;
            }
            if(touchDown(Button_MIN,75)){
              CP[plan].savetimerA[countCP]--;
            }
          } else if(selectSet == 4){
            lcd_char(1, 0, 45, ">", true, false, false);
            if(touchDown(Button_PLUS,75)){
              CP[plan].saveReadIdx[countCP]++;
              if(CP[plan].saveReadIdx[countCP] > 99) CP[plan].saveReadIdx[countCP]= 0;
            }
            if(touchDown(Button_MIN,75)){
              CP[plan].saveReadIdx[countCP]--;
              if(CP[plan].saveReadIdx[countCP] == 255) CP[plan].saveReadIdx[countCP] = 99;
            }
          }
          
          sprintf(buff , "PLAN-%d : CP-%d" , plan+1 , countCP);
          lcd_char(1, 10, 5,  buff, true, false, false);
          lcd_char(1, 10, 15, "ACTION: " + String(actCheckpoint[CP[plan].saveAct[countCP]]), true, false, false);
          lcd_char(1, 10, 25, "D ACT : " + String(CP[plan].saveiDelay[countCP]) + " mS", true, false, false);
          lcd_char(1, 10, 35, "SET TA: " + String(CP[plan].savetimerA[countCP]) + " mS" , true, false, false);
          lcd_char(1, 10, 45, "READIX: " + String(CP[plan].saveReadIdx[countCP]), true, false, false);
          lcd.display();
        }
}