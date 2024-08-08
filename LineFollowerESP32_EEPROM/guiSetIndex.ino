void setIDX() {
  oledClear();
  bool stateMode = false;
  initEncoder(true);
  menuIdx=1;
  while (1) {
    lcd_char(1, 38, 5, "Plan - " + String(plan+1) , true , false , true);
    if (touchUp(Button_UP)) {
      menuIdx++;
      if (menuIdx > 4) menuIdx = 1;
    }
    if (touchUp(Button_DOWN)) {
      menuIdx--;
      if (menuIdx < 1) menuIdx = 4;
    }
    if (touchUp(Button_RUN)) {
      menuIdx = selectSet = halIdx = menuCount = 0;
      saveIdxAll();
      break;
    }

    if (menuIdx == 1) {
      if (touchUp(Button_OK)) {
        IdIdx = 0;
        countIdx = 0;
        halIdx = 1;
        stateIdxM = true;
      }
      lcd.fillRoundRect(2, 18, 60, 15, 3,  SH110X_WHITE);
      lcd_char(1, 5, 23, "(00 - 24)", false , false, false);
    } else {
      lcd.fillRoundRect(2, 18, 60, 15, 3,  SH110X_BLACK);
      lcd_char(1, 5, 23, "(00 - 24)", true , false , true);
   
    }

    if (menuIdx == 2) {
      if (touchUp(Button_OK)) {
        IdIdx = 1;
        countIdx = 25;
        halIdx = 1;
        stateIdxM = true;
      }
 
      lcd.fillRoundRect(65, 18, 60, 15, 3,  SH110X_WHITE);
      lcd_char(1, 68, 23, "(25 - 30)", false , false, false);
    } else {
      lcd.fillRoundRect(65, 18, 60, 15, 3,  SH110X_BLACK);
      lcd_char(1, 68, 23, "(25 - 30)", true , false , true);
    }

    if (menuIdx == 3) {
      if (touchUp(Button_OK)) {
        IdIdx = 2;
        countIdx = 51;
        halIdx = 1;
        stateIdxM = true;
      }
     lcd.fillRoundRect(2, 40, 60, 15, 3,  SH110X_WHITE);
      lcd_char(1, 5, 45, "(51 - 75)", false , false, false);
    } else {
      lcd.fillRoundRect(2, 40, 60, 15, 3,  SH110X_BLACK);
      lcd_char(1, 5, 45, "(51 - 75)", true , false , true); 
    }

    if (menuIdx == 4) {
      if (touchUp(Button_OK)) {
        IdIdx = 3;
        countIdx = 76;
        halIdx = 1;
        stateIdxM = true;
      }
      lcd.fillRoundRect(65, 40, 60, 15, 3,  SH110X_WHITE);
      lcd_char(1, 68, 45, "(76 - 99)", false , false, false);
    } else {
      lcd.fillRoundRect(65, 40, 60, 15, 3,  SH110X_BLACK);
      lcd_char(1, 68, 45, "(76 - 99)", true , false , true);
    }

    while (stateIdxM) {
      if (touchUp(Button_RUN)) {
        menuCount = selectSet = 0;
        stateIdxM = false;
        oledClear();
        break;
      }

      if (halIdx == 1) {
        headUpIdx(true, false);
        if (touchUp(Button_UP)) {
          if (--selectSet == 254) {
            selectSet = 0;
            menuCount = 0;
          }
        }
        if (touchUp(Button_DOWN)) {
          if (++selectSet > 2) {
            selectSet = 1;
            menuCount = 0;
            halIdx = 2;
          }
        }

        if (selectSet == 255) {
          lcd.drawRect(47, 0, 40, 10, SH110X_WHITE);
          if (touchDown(Button_PLUS , 150)) {
            countIdx++;
          }
          if (touchDown(Button_MIN, 150)) {
            countIdx--;
          }
        }

        switch (IdIdx) {
          case 0:
            if (countIdx >= 24) countIdx = 24;
            else if ( countIdx <= 0) countIdx = 0;
            break;
          case 1:
            if (countIdx >= 50) countIdx = 50;
            else if (countIdx <= 25) countIdx = 25;
            break;
          case 2:
            if (countIdx >= 75) countIdx = 75;
            else if (countIdx <= 51) countIdx = 51;
            break;
          case 3:
            if (countIdx >= 99) countIdx = 99;
            else if (countIdx <= 76) countIdx = 76;
            break;
        }

        if (selectSet == 1) {
          if (touchUp(Button_OK)) {
            if (++menuCount > 3) menuCount = 1;
          }
          if (menuCount == 1) {
            lcd.drawRect(23, 13, 48, 11, SH110X_WHITE);
            if (touchDown(Button_PLUS , 150)) {
              trigW[plan][countIdx]++;
              if (trigW[plan][countIdx] > 1) trigW[plan][countIdx] = 0;
            }
            if (touchDown(Button_MIN, 150)) {
              trigW[plan][countIdx]--;
              if (trigW[plan][countIdx] == 255) trigW[plan][countIdx] = 1;
            }
          }
          if (menuCount == 2) {
            lcd.drawRect(70, 13, 54, 11, SH110X_WHITE);
            if (touchDown(Button_PLUS , 150)) {
              logic[plan][countIdx]++;
              if (logic[plan][countIdx] > 3) logic[plan][countIdx] = 0;
            }
            if (touchDown(Button_MIN, 150)) {
              logic[plan][countIdx]--;
              if (logic[plan][countIdx] == 255) logic[plan][countIdx] = 3;
            }
          }
          if (menuCount == 3) {
            lcd.drawRect(22, 22, 95, 16, SH110X_WHITE);
            if (touchDown(Button_PLUS , 150)) {
              sensLogIdx[plan][countIdx]++;
              if (sensLogIdx[plan][countIdx] > 23) sensLogIdx[plan][countIdx] = 0;
            }
            if (touchDown(Button_MIN, 150)) {
              sensLogIdx[plan][countIdx]--;
              if (sensLogIdx[plan][countIdx] == 255) sensLogIdx[plan][countIdx] = 23;
            }
          }
          dispSensorIdx(sensLog[sensLogIdx[plan][countIdx]]);
          sprintf(buff, "Trig:%s Logic:%s", slctTrig[trigW[plan][countIdx]], logika[logic[plan][countIdx]]);
          lcd_char(1, 25, 15, buff, true, false, false);
          lcd.fillRect(3, 19, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 21, "T", false, false, false);
        } else {
          dispSensorIdx(sensLog[sensLogIdx[plan][countIdx]]);
          sprintf(buff, "Trig:%s Logic:%s", slctTrig[trigW[plan][countIdx]], logika[logic[plan][countIdx]]);
          lcd_char(1, 25, 15, buff, true, false, false);
          lcd.drawRect(3, 19, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 21, "T", true, false, false);
        }

        if (selectSet == 2) {
          if (touchUp(Button_OK)) {
            if (++menuCount > 3) menuCount = 1;
          }
          if (menuCount == 1) {
            if (touchDown(Button_PLUS , 150)) {
              idx[plan][countIdx]++;
              if (idx[plan][countIdx] > 9) idx[plan][countIdx] = 0;
            }
            if (touchDown(Button_MIN, 150)) {
              idx[plan][countIdx]--;
              if (idx[plan][countIdx] == 255) idx[plan][countIdx] = 9;
            }
            lcd.drawRect(23, 38, 80, 11, SH110X_WHITE);
          }
          if (menuCount == 2) {
            if (touchDown(Button_PLUS , 150)) {
              spdL[plan][countIdx] = spdL[plan][countIdx] + 5;
            }
            if (touchDown(Button_MIN, 150)) {
              spdL[plan][countIdx] = spdL[plan][countIdx] - 5;
            }
            lcd.drawRect(24, 47, 36, 11, SH110X_WHITE);
          }
          if (menuCount == 3) {
            if (touchDown(Button_PLUS , 150)) {
              spdR[plan][countIdx] = spdR[plan][countIdx] + 5;
            }
            if (touchDown(Button_MIN, 150)) {
              spdR[plan][countIdx] = spdR[plan][countIdx] - 5;
            }
            lcd.drawRect(60, 47, 36, 11, SH110X_WHITE);
          }
          sprintf(buff, "Then %s", act[idx[plan][countIdx]]);
          lcd_char(1, 25, 40, buff, true, false, false);
          if (idx[plan][countIdx] == 1 ) sprintf(buff, "L:%03d R:%03d", spdL[plan][countIdx], spdR[plan][countIdx]);
          else if (idx[plan][countIdx] == 2) sprintf(buff, "L:-%03d R:%03d", spdL[plan][countIdx], spdR[plan][countIdx]);
          else if (idx[plan][countIdx] == 3) sprintf(buff, "L:%03d R:-%03d", spdL[plan][countIdx], spdR[plan][countIdx]);
          else if (idx[plan][countIdx] == 4) sprintf(buff, "L:-%03d R:-%03d", spdL[plan][countIdx], spdR[plan][countIdx]);
          else sprintf(buff, "L:--- R:---");
          lcd_char(1, 25, 49, buff, true, false, false);
          lcd.fillRect(3, 40, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 42, "A", false, false, false);
        } else {
          sprintf(buff, "Then %s", act[idx[plan][countIdx]]);
          lcd_char(1, 25, 40, buff, true, false, false);
          if (idx[plan][countIdx] == 1 ) sprintf(buff, "L:%03d R:%03d", spdL[plan][countIdx], spdR[plan][countIdx]);
          else if (idx[plan][countIdx] == 2) sprintf(buff, "L:-%03d R:%03d", spdL[plan][countIdx], spdR[plan][countIdx]);
          else if (idx[plan][countIdx] == 3) sprintf(buff, "L:%03d R:-%03d", spdL[plan][countIdx], spdR[plan][countIdx]);
          else if (idx[plan][countIdx] == 4) sprintf(buff, "L:-%03d R:-%03d", spdL[plan][countIdx], spdR[plan][countIdx]);
          else sprintf(buff, "L:--- R:---");
          lcd_char(1, 25, 49, buff, true, false, false);
          lcd.drawRect(3, 40, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 42, "A", true, false, false);
        }
      } // end bracket page 1 setIdx

      if (halIdx == 2) {
        headUpIdx(true, false);
        if (touchUp(Button_UP)) {
          if (--selectSet == 255) {
            selectSet = 2;
            menuCount = 0;
            halIdx = 1;
          }
        }
        if (touchUp(Button_DOWN)) {
          if (++selectSet > 2) {
            selectSet = 1;
            menuCount = 0;
            halIdx = 3;
          }
        }

        if (selectSet == 1) {
          if (touchUp(Button_OK)) {
            if (++menuCount > 1) menuCount = 1;
          }
          if (touchDown(Button_PLUS , 150)) {
            idelay[plan][countIdx] += 2;
          }
          if (touchDown(Button_MIN, 150)) {
            idelay[plan][countIdx] -= 2;
          }
          sprintf(buff, "%s for", act[idx[plan][countIdx]]);
          lcd_char(1, 25, 15, buff, true, false, false);
          sprintf(buff, "D: %d ms", idelay[plan][countIdx]);
          lcd_char(1, 25, 25, buff, true, false, false);
          lcd.fillRect(3, 19, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 21, "B", false, false, false);
        }
        else {
          sprintf(buff, "%s for", act[idx[plan][countIdx]]);
          lcd_char(1, 25, 15, buff, true, false, false);
          sprintf(buff, "D: %d ms", idelay[plan][countIdx]);
          lcd_char(1, 25, 25, buff, true, false, false);
          lcd.drawRect(3, 19, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 21, "B", true, false, false);
        }

        if (selectSet == 2) {
          if (touchDown(Button_PLUS , 150)) {
            clrLine[plan][countIdx] = 1;
          }
          if (touchDown(Button_MIN, 150)) {
            clrLine[plan][countIdx] = 0;
          }
          lcd_char(1, 25, 40, "Run on line", true, false, false);
          sprintf(buff, "%s", clrLineI[clrLine[plan][countIdx]]);
          lcd_char(1, 25, 49, buff, true, false, false);
          lcd.fillRect(3, 40, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 42, "C", false, false, false);
        }
        else {
          lcd_char(1, 25, 40, "Run on line", true, false, false);
          sprintf(buff, "%s", clrLineI[clrLine[plan][countIdx]]);
          lcd_char(1, 25, 49, buff, true, false, false);
          lcd.drawRect(3, 40, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 42, "C", true, false, false);
        }
      } // end bracket page 2 setIdx

      if (halIdx == 3) {
        headUpIdx(true, false);
        if (touchUp(Button_UP)){
          if (--selectSet == 255) {
            selectSet = 2;
            menuCount = 0;
            halIdx = 2;
          }
        }
        if (touchUp(Button_DOWN)) {
          if (++selectSet > 2) {
            selectSet = 1;
            menuCount = 0;
            halIdx = 4;
          }
        }

        if (selectSet == 1) {
          if (touchUp(Button_OK)) {
            if (++menuCount > 3) menuCount = 1;
          }
          if (menuCount == 1) {
            if (touchDown(Button_PLUS , 150)) {
              speedA[plan][countIdx] += 5;
            }
            if (touchDown(Button_MIN, 150)) {
              speedA[plan][countIdx] -= 5;
            }
            lcd.drawRect(23, 23, 36, 11, SH110X_WHITE);
          }
          else if (menuCount == 2) {
            if (touchDown(Button_PLUS , 150)) {
              timerA[plan][countIdx] += 1;
            }
            if (touchDown(Button_MIN, 150)) {
              timerA[plan][countIdx] -= 1;
            }
            lcd.drawRect(60, 23, 42, 11, SH110X_WHITE);
          }
          else if(menuCount == 3){
            if(touchDown(Button_PLUS , 150)){
              modeTIM[plan][countIdx]++;
              if(modeTIM[plan][countIdx] > 2) modeTIM[plan][countIdx] = 0;
            }
            if(touchDown(Button_MIN, 150)){
              modeTIM[plan][countIdx]--;
              if(modeTIM[plan][countIdx] == 255) modeTIM[plan][countIdx] = 2;
            }
          lcd.drawRect(98, 23, 25, 11, SH110X_WHITE);
          if(modeTIM[plan][countIdx] == 1){
            timerA[plan][countIdx] = measureLengthR();
          } else if(modeTIM[plan][countIdx] == 2){
            timerA[plan][countIdx] = measureLengthL();
            }
          }
          
          lcd_char(1, 25, 15, "Then Set SA", true, false, false);
          sprintf(buff, "V:%03d T:%04d %s", speedA[plan][countIdx], timerA[plan][countIdx], slctMode[modeTIM[plan][countIdx]]);
          lcd_char(1, 25, 25, buff, true, false, false);
          lcd.fillRect(3, 19, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 21, "D", false, false, false);
        }
        else {
          lcd_char(1, 25, 15, "Then Set SA", true, false, false);
          sprintf(buff, "V:%03d T:%04d %s", speedA[plan][countIdx], timerA[plan][countIdx], slctMode[modeTIM[plan][countIdx]]);
          lcd_char(1, 25, 25, buff, true, false, false);
          lcd.drawRect(3, 19, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 21, "D", true, false, false);
        }

        if (selectSet == 2) {
          if (touchUp(Button_OK)) {
            if (++menuCount > 2) menuCount = 1;
          }
          if (menuCount == 1) {
            if (touchDown(Button_PLUS , 150)) {
              speedB[plan][countIdx] += 5;
            }
            if (touchDown(Button_MIN, 150)) {
              speedB[plan][countIdx] -= 5;
            }
            lcd.drawRect(23, 47, 36, 11, SH110X_WHITE);
          }
          else if (menuCount == 2) {
            if (touchDown(Button_PLUS , 150)) {
              timerB[plan][countIdx] += 1;
            }
            if (touchDown(Button_MIN, 150)) {
              timerB[plan][countIdx] -= 1;
            }
            lcd.drawRect(60, 47, 42, 11, SH110X_WHITE);
          }
          lcd_char(1, 25, 40, "Then Set SB", true, false, false);
          sprintf(buff, "V:%03d T:%04d mS", speedB[plan][countIdx], timerB[plan][countIdx]);
          lcd_char(1, 25, 49, buff, true, false, false);
          lcd.fillRect(3, 40, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 42, "E", false, false, false);
        }
        else {
          lcd_char(1, 25, 40, "Then Set SB", true, false, false);
          sprintf(buff, "V:%03d T:%04d mS", speedB[plan][countIdx], timerB[plan][countIdx]);
          lcd_char(1, 25, 49, buff, true, false, false);
          lcd.drawRect(3, 40, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 42, "E", true, false, false);
        }
      } // end bracket page 3 setIdx

      if (halIdx == 4) {
        headUpIdx(true, false);
        if (touchUp(Button_UP)) {
          if (--selectSet == 255) {
            selectSet = 2;
            menuCount = 0;
            halIdx = 3;
          }
        }
        if (touchUp(Button_DOWN)) {
          if (++selectSet > 2) {
            selectSet = 2;
            menuCount = 0;
          }
        }

        if (selectSet == 1) {
          if (touchUp(Button_OK)) {
            if (++menuCount > 3) menuCount = 1;
          }
          if (touchDown(Button_PLUS , 150)) {
            if(++pidProfile[plan][countIdx] > 6) pidProfile[plan][countIdx] = 0;
          }
          if (touchDown(Button_MIN, 150)) {
            if(--pidProfile[plan][countIdx] == 255) pidProfile[plan][countIdx] = 6;
          }
          lcd_char(1, 25, 15, "PID Profile :", true, false, false);
          sprintf(buff, "%s", slctPID[pidProfile[plan][countIdx]]);
          lcd_char(1, 25, 25, buff, true, false, false);
          lcd.fillRect(3, 19, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 21, "F", false, false, false);
        }
        else {
          lcd_char(1, 25, 15, "PID Profile :", true, false, false);
          sprintf(buff, "%s", slctPID[pidProfile[plan][countIdx]]);
          lcd_char(1, 25, 25, buff, true, false, false);
          lcd.drawRect(3, 19, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 21, "F", true, false, false);
        }

        if (selectSet == 2) {
          
          lcd.fillRect(3, 40, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 42, "H", false, false, false);
        }
        else {
          
          lcd.drawRect(3, 40, 18, 18, SH110X_WHITE);
          lcd_char(2, 7, 42, "H", true, false, false);
        }
      } // end Bracket hal 4
      
      lcd.display();
    } // end while M Idx
    lcd.display();
  }
}