
void CMIDX() {
  const char* mode []= { "copy" , "mirror"};
  char modCopy[2][7] = {"COPY", "MIRROR"};
  byte x1, x2;
  byte selectModeCM = 0;
  byte steps = 0;
  bool doneCM = false;
  selectSet = 0;
  while (1) {
    headCMIDX:
    headUp(true, false);
    if (touchUp(Button_RUN)) {
      oledClear();
      break;
    }
    if (touchUp(Button_UP)) {
      selectSet--;
      if (selectSet == 255) selectSet = 3;
    }
    if (touchUp(Button_DOWN)) {
      selectSet++;
      if (selectSet > 3) selectSet = 0;
    }

    if (selectSet == 0) {
      lcd_char(1, 0, 15, ">", true, false, false);
      if (touchUp(Button_PLUS)) {
        selectModeCM++;
        if (selectModeCM > 1) selectModeCM = 1;
      }
      if (touchUp(Button_MIN)) {
        selectModeCM--;
        if (selectModeCM == 255) selectModeCM = 0;
      }
    }
    else if (selectSet == 1) {
      lcd_char(1, 0, 25, ">", true, false, false);
      if (touchUp(Button_PLUS)) {
        x1++;
        if (x1 > 4) x1 = 4;
      }
      if (touchUp(Button_MIN)) {
        x1--;
        if (x1 == 255) x1 = 0;
      }
    }
    else if (selectSet == 2) {
      lcd_char(1, 0, 35, ">", true, false, false);
      if (touchUp(Button_PLUS)) {
        x2++;
        if (x2 > 4) x2 = 4;
      }
      if (touchUp(Button_MIN)) {
        x2--;
        if (x2 <= 255) x2 = 0;
      }
    }
    else if (selectSet == 3) {
      lcd_char(1, 0, 45, ">", true, false, false);
      if (touchUp(Button_OK)) {
        if (x1 == x2) {
          lcd_char(1, 10, 20, "Invalid Same Plan!", true, true, true);
          delay(2000);
          oledClear();
          goto headCMIDX;
        } else {
          oledClear();
          steps = 1;
        }
      }
    }
    sprintf(buff, "Mode : %s" , modCopy[selectModeCM]);
    lcd_char(1, 10, 15, buff, true, false, false);
    lcd_char(1, 10, 25, "Plan: " + String(x1 + 1), true, false, false);
    lcd_char(1, 10, 35, "ke Plan: " + String(x2 + 1), true, false, false);
    lcd_char(1, 10, 45, "OK->", true, false, false);
    if (steps == 1) {
      if (selectModeCM == 0) { // Mode Normal
        oledClear();
        for (byte i = 0; i < 100; i++) {
          idx[x2][i] = idx[x1][i];
          logic[x2][i] = logic[x1][i];
          sensLogIdx[x2][i] = sensLogIdx[x1][i];
          trigW[x2][i] = trigW[x1][i];
          spdR[x2][i] = spdR[x1][i];
          spdL[x2][i] = spdL[x1][i];
          idelay[x2][i] = idelay[x1][i];
          timerA[x2][i] = timerA[x1][i];
          timerB[x2][i] = timerB[x1][i];
          speedA[x2][i] = speedA[x1][i];
          speedB[x2][i] = speedB[x1][i];
          clrLine[x2][i] = clrLine[x1][i];
          pidProfile[x2][i] = pidProfile[x1][i];
          modeTIM[x2][i] = modeTIM[x1][i];
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
          

          trigW[x2][i] = trigW[x1][i];
          spdR[x2][i] = spdR[x1][i];
          spdL[x2][i] = spdL[x1][i];
          idelay[x2][i] = idelay[x1][i];
          timerA[x2][i] = timerA[x1][i];
          timerB[x2][i] = timerB[x1][i];
          speedA[x2][i] = speedA[x1][i];
          speedB[x2][i] = speedB[x1][i];
          clrLine[x2][i] = clrLine[x1][i];
          pidProfile[x2][i] = pidProfile[x1][i];
          modeTIM[x2][i] = modeTIM[x1][i];
          lcd_loading(1, 29, i, true, false, false);
          lcd.display();
          delay(10);
          if (i == 99) {
            saveIdxAll();
            doneCM = true;
          }
        }
      } // end select mode 1 CM
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
