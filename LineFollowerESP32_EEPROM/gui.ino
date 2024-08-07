void menu() {
  countMenu = 1;
  halaman = 0 ;

  saveAll();
  delay(10);
  while (1) {
    stopMotor();
    if (touchUp(Button_UP) ) {
      if (countMenu == 1 && halaman == 0 ) {
        countMenu = 5;
        halaman = 1;
        oledClear();
      }
      if (countMenu == 1  && halaman == 1 ) {
        countMenu = 5;
        halaman = 0;
        oledClear();
      }
      countMenu--;
    }
    if (touchUp(Button_DOWN)) {
       if (countMenu == 4 && halaman == 0 ) {
        countMenu = 0;
        halaman = 1;
        oledClear();
      }
      if (countMenu == 4 && halaman == 1 ) {
        countMenu = 0;
        halaman = 0;
        oledClear();
      }
      countMenu++;
    }

    if (touchUp(Button_RUN)) {
      oledClear();
      break;
    }

    if (halaman == 0) {
      headUp(true, false);
      if (countMenu == 1) {
        if (touchUp(Button_OK)) {
          setIDX();
        }
        lcd.fillRect(0, 14, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 15, "1. Setting Index", false, false, false);
      } else {
        lcd_char(1, 2, 15, "1. Setting Index", true, false, false);
      }

      if (countMenu == 2) {
        if (touchUp(Button_OK)) {
          calibSensor();
        }
        lcd.fillRect(0, 24, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 27, "2. Kalibrasi Sensor", false, false, false);
      } else {
        lcd_char(1, 2, 27, "2. Kalibrasi Sensor", true, false, false);
      }

      if (countMenu == 3) {
        if (touchUp(Button_OK)) {
          TunePid();
        }
        lcd.fillRect(0, 34, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 37, "3. Tuning PID", false, false, false);
      } else {
        lcd_char(1, 2, 37, "3. Tuning PID", true, false, false);
      }

      if (countMenu == 4) {
        if (touchUp(Button_OK)) {
          CMIDX();
        }
        lcd.fillRect(0, 44, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 47, "4. Copy/Mirror Plan", false, false, false);
      } else {
        lcd_char(1, 2, 47, "4. Copy/Mirror Plan", true, false, false);
      }
    } else if (halaman == 1) {
      headUp(true, false);
      if (countMenu == 1) {
        if (touchUp(Button_OK)) {
          oledClear();
          byte steps = 0;
          byte speedsR = 0;
          byte speedsL = 0;
          char Sdirection[3][3] = {"F", "B" , "S" };
          byte selectDirectR = 0;
          byte selectDirectL = 0;
          menuCount = 0;
          initEncoder(true);
          while (1) {
            headUp(true, false);
            if (touchUp(Button_RUN)) {
              speedsR = speedsL = 0;
              pwmMotor(0, 0);
              stopMotor();
              initEncoder(false);
              break;
            }
            if (touchUp(Button_UP)) {
              menuCount++;
              if (menuCount > 2) menuCount = 1;
            }
            if (touchUp(Button_DOWN)) {
              menuCount--;
              if (menuCount == 0 || menuCount == 255) menuCount == 2;
            }

            if (menuCount == 1) {
              if (touchUp(Button_OK)) {
                steps++;
                if (steps > 2) steps = 0;
              }
              if (steps == 1) {
                lcd_char(1, 65, 30, ">", true, false, false);
                if (touchUp(Button_PLUS )) {
                  selectDirectR++;
                  if (selectDirectR > 2) selectDirectR = 0;
                }
                if (touchUp(Button_MIN)) {
                  selectDirectR--;
                  if (selectDirectR == 255) selectDirectR == 2;
                }
              }
              else if (steps == 2) {
                lcd_char(1, 65, 40, ">", true, false, false);
                if (touchDown(Button_PLUS , 50)) {
                  speedsR+=5;
                  if (speedsR > 255) speedsR = 255;
                }
                if (touchDown(Button_MIN , 50)) {
                  speedsR-=5;
                  if (speedsR < 0) speedsR == 255;
                }
              }
              sprintf(buff, "Direct: %s", Sdirection[selectDirectR]);
              lcd_char(1, 70, 30, buff, true, false, false);
              lcd_char(1, 70, 40, "Speed:" + String(speedsR), true, false, false);
              lcd_char(1, 70, 50, "RPM: " + String(rpmR), true, false, false);
              lcd.fillRoundRect(65, 15, 60, 12, 2, SH110X_WHITE);
              lcd_char(1, 67, 17, "MTR Kanan", false, false, false);
            } else {
               lcd_char(1, 70, 40, "Speed:" + String(speedsR), true, false, false);
               lcd_char(1, 70, 50, "RPM: " + String(rpmR), true, false, false);
               lcd.drawRoundRect(65, 15, 60, 12, 2, SH110X_WHITE);
               lcd_char(1, 67, 17, "MTR Kanan", true, false, false);
            }

            if (menuCount == 2) {
              if (touchUp(Button_OK)) {
                steps++;
                if (steps > 2) steps = 0;
              }
              if (steps == 1) {
                lcd_char(1, 0, 30, ">", true, false, false);
                if (touchUp(Button_PLUS)) {
                  selectDirectL++;
                  if (selectDirectL > 2) selectDirectL = 0;
                }
                if (touchUp(Button_MIN)) {
                  selectDirectL--;
                  if (selectDirectL == 255) selectDirectL == 2;
                }
              }
              else if (steps == 2) {
                lcd_char(1, 0, 40, ">", true, false, false);
                if (touchDown(Button_PLUS , 50)) {
                  speedsL+=5;
                  if (speedsL > 255) speedsL = 255;
                }
                if (touchDown(Button_MIN , 50)) {
                  speedsL-=5;
                  if (speedsL < 0) speedsL == 255;
                }
              }
              sprintf(buff, "Direct: %s", Sdirection[selectDirectL]);
              lcd_char(1, 5, 30, buff, true, false, false);
              lcd_char(1, 5, 40, "Speed:" + String(speedsL), true, false, false);
              lcd_char(1, 5, 50, "RPM: " + String(rpmL), true, false, false);
              lcd.fillRoundRect(0, 15, 60, 12, 2, SH110X_WHITE);
              lcd_char(1, 2, 17, "MTR Kiri", false, false, false);
            } else {
              lcd_char(1, 5, 40, "Speed:" + String(speedsL), true, false, false);
              lcd_char(1, 5, 50, "RPM: " + String(rpmL), true, false, false);
              lcd.drawRoundRect(0, 15, 60, 12, 2, SH110X_WHITE);
              lcd_char(1, 2, 17, "MTR Kiri", true, false, false);
            }
            pwmMotor(selectDirectL == 0 ? speedsL : speedsL * -1, selectDirectR == 0 ? speedsR : speedsR * -1);
            if(selectDirectL == 2)stopMotorL();
            if(selectDirectR == 2)stopMotorR();
            
//            pwmMotor(selectDirectL == 0 ? map2(speedsL, 0, 100, 0, 255) : map2(speedsL, 0, 100, 0, 255) * -1,  selectDirectR == 0 ? map2(speedsR, 0, 100, 0, 255) : map2(speedsR, 0, 100, 0, 255) * -1);
            lcd.display();
          }
        }
        lcd.fillRect(0, 14, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 15, "5. Motor", false, false, false);
      } else {
        lcd_char(1, 2, 15, "5. Motor", true, false, false);
      }

      if (countMenu == 2) {
        if (touchUp(Button_OK)) {
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
              sprintf(buff, "P:%d Yakin Dihapus ?", selectPlan + 1);
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
              if(touchUp(Button_PLUS)){
                if(++selectPlan > 4) selectPlan = 4;
              }
              if(touchUp(Button_MIN)){
                if(--selectPlan == 255) selectPlan = 0;
              }
              if(menuCount == 1){
                lcd.drawRoundRect(18, 33, 22, 12, 2, SH110X_WHITE);
                if(touchUp(Button_OK)) steps = 2;
              } else if(menuCount == 0){
                lcd.drawRoundRect(68, 33, 38, 12, 2, SH110X_WHITE);
                if(touchUp(Button_OK)) break;
              }
            }
            else if (steps == 2) {
              for (byte i = 0; i < VAL_INDEX; i++) {
                  idx[selectPlan][i] = 0;
                  logic[selectPlan][i] = 0;
                  sensLogIdx[selectPlan][i] = 0;
                  trigW[selectPlan][i] = 0;
                  spdR[selectPlan][i] = 100;
                  spdL[selectPlan][i] = 100;
                  idelay[selectPlan][i] = 0;
                  timerA[selectPlan][i] = 0;
                  timerB[selectPlan][i] = 0;
                  speedA[selectPlan][i] = 0;
                  speedB[selectPlan][i] = 0;
                  clrLine[selectPlan][i] = 0;
                  pidProfile[selectPlan][i] = 0;
                  modeTIM[selectPlan][i] = 0;
                }
              delay(50);
              steps = 3;
            }
            else if (steps == 3) {
              headUp(true, false);
              lcd_char(1, 30, 35, "Selesai!!", true, false, false);
              saveIdxAll();
              lcd.display();
              delay(2000);
              break;
            }
            lcd.display();
          } // end bracket while true
        }
        lcd.fillRect(0, 24, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 27, "6. Reset Plan", false, false, false);
      } else {
        lcd_char(1, 2, 27, "6. Reset Plan", true, false, false);
      }

      if (countMenu == 3) {
        lcd.fillRect(0, 34, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 37, "7. Update OS", false, false, false);
      } else {

        lcd_char(1, 2, 37, "7. Update OS", true, false, false);
      }

      if (countMenu == 4) {
        lcd.fillRect(0, 44, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 47, "8. System Setting", false, false, false);
        if(touchUp(Button_OK)){
         menuSetting();

        }
      }
       else {
        lcd_char(1, 2, 47, "8. System Setting", true, false, false);
    }
      } 
    lcd.display();
  } // end bracket while
} // end Function Menu()

void setIDX() {
  oledClear();
  bool stateMode = false;
  initEncoder(true);
  while (1) {
    if (touchUp(Button_DOWN)) {
      menuIdx++;
      if (menuIdx > 4) menuIdx = 0;
    }
    if (touchUp(Button_UP)) {
      menuIdx--;
      if (menuIdx == 255) menuIdx = 4;
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
      lcd.fillRect(2, 18, 60, 15, SH110X_WHITE);
      lcd_char(1, 5, 23, "(00 - 24)", false, false, false);
    } else {
      lcd.drawRect(2, 18, 60, 15, SH110X_WHITE);
      lcd_char(1, 5, 23, "(00 - 24)", true, false, false);
    }

    if (menuIdx == 2) {
      if (touchUp(Button_OK)) {
        IdIdx = 1;
        countIdx = 25;
        halIdx = 1;
        stateIdxM = true;
      }
      lcd.fillRect(65, 18, 60, 15, SH110X_WHITE);
      lcd_char(1, 68, 23, "(25 - 50)", false, false, false);
    } else {
      lcd.drawRect(65, 18, 60, 15, SH110X_WHITE);
      lcd_char(1, 68, 23, "(25 - 50)", true, false, false);
    }

    if (menuIdx == 3) {
      if (touchUp(Button_OK)) {
        IdIdx = 2;
        countIdx = 51;
        halIdx = 1;
        stateIdxM = true;
      }
      lcd.fillRect(2, 40, 60, 15, SH110X_WHITE);
      lcd_char(1, 5, 45, "(51 - 75)", false, false, false);
    } else {
      lcd.drawRect(2, 40, 60, 15, SH110X_WHITE);
      lcd_char(1, 5, 45, "(51 - 75)", true, false, false);
    }

    if (menuIdx == 4) {
      if (touchUp(Button_OK)) {
        IdIdx = 3;
        countIdx = 76;
        halIdx = 1;
        stateIdxM = true;
      }
      lcd.fillRect(65, 40, 60, 15, SH110X_WHITE);
      lcd_char(1, 68, 45, "(76 - 99)", false, false, false);
    } else {
      lcd.drawRect(65, 40, 60, 15, SH110X_WHITE);
      lcd_char(1, 68, 45, "(76 - 99)", true, false, false);
    }

    while (stateIdxM) {
      if (touchUp(Button_RUN)) {
        menuCount = selectSet = 0;
        stateIdxM = false;
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

void readCounter(byte count) {
  int16_t speedPlayR, speedPlayL = 0;
  int16_t speedL, speedR;

  switch (count) { // stop
    case 0:
      stopMotor();
      break;

    case 1: // maju
      speedPlayL = spdL[plan][countIdxPlay];
      speedL = speedPlayL / 4;
      lastTimeIdxPlay = timeIdxPlay;
      while (1) {
        if (speedL < speedPlayL) {
          speedL += 2;
          if (speedL > speedPlayL) {
            speedL = speedPlayL;
          }
        }
        speedOne(speedL);
        if (timeIdxPlay - lastTimeIdxPlay >= idelay[plan][countIdxPlay]) break;
        if(countCP != 0){
          if (timeIdxPlay - lastTimeIdxPlay >= iDelayCheckpoint[plan][countCP]) break;
        }
        
      }
      lastTimeIdxPlay = 0;
      break;

    case 2: // kiri
      pwmMotor(spdL[plan][countIdxPlay] * -1, spdR[plan][countIdxPlay]);
      delay(idelay[plan][countIdxPlay]);
      break;

    case 3: // kanan
      pwmMotor(spdL[plan][countIdxPlay], spdR[plan][countIdxPlay] * -1);
      delay(idelay[plan][countIdxPlay]);
      break;

    case 4: // mundur
      speedPlayL = spdL[plan][countIdxPlay];
      speedL = speedPlayL / 4;
      timeIdxPlay = 0;
      while (1) {
        if (speedL < speedPlayL) {
          speedL += 2;
          if (speedL > speedPlayL) {
            speedL = speedPlayL;
          }
        }
        speedOne(speedL * -1);
        if (timeIdxPlay - lastTimeIdxPlay >= idelay[plan][countIdxPlay]) break;
      }
      lastTimeIdxPlay = 0;
      break;

    case 7: // TLeft
    while(1){
    pwmMotor(-200, 200);
    delay(idelay[plan][countIdxPlay]);
    if(readSensor() & 0b00000011000000){break;}
    else if(readSensor() & 0b11111100111111){break;}
    } // end while bracket
    break;

    case 8: // TRight
    while(1){
    pwmMotor(200, -200);
    delay(idelay[plan][countIdxPlay]);
    if(readSensor() & 0b00000011000000){break;}
    else if(readSensor() & 0b11111100111111){break;}
    } // end while bracket
    break;
  }
}

void CMIDX() {
  const char* mode []= { "copy" , "mirror"};
  char modCopy[2][7] = {"COPY", "MIRROR"};
  byte x1, x2;
  byte selectModeCM = 0;
  byte steps = 0;
  bool doneCM = false;
  selectSet = 0;
  while (1) {
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
          lcd_char(1, 40, 35, "Invalid", true, true, true);
          delay(5000);
          oledClear();
          break;
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
            lcd_char(1, 30, 35, "Plan " + String(x1) + " telah " , true, false , false);
            lcd_char(1, 40, 35, "ter" + String(mode[selectModeCM]) + " di Plan " + String(x2) + " !!!" , true, false , false);
            // saveIdxAll();
            delay(3000);
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
          delay(25);
          if (i == 99) {
            lcd_char(1, 30, 35, "Plan " + String(x1) + " telah " , true, false, false);
            lcd_char(1, 40, 35, "ter" + String(mode[selectModeCM]) + " di Plan " + String(x2) + " !!!" , true, false, false);
            saveIdxAll();
            delay(3000);
            doneCM = true;
          }
        }
      } // end select mode 1 CM
    }
    if(doneCM){
      oledClear();
      break;
    }
    lcd.display();
  }
}

void menuSetting (){
      oledClear();
      const char* set[] = {"OFF" , "ON"};
      const char* mode_lf[] = {"TRANSPORTER" , "LINE TRACER"};
      const char* set_wifi[] = {"Disconnect" , "Connected"};
      byte conWifi = 0 ; // PR con wifi
      while(1){
      headUp(true, false);
      if(touchUp(Button_RUN))break;
      if(touchUp(Button_DOWN)) {
        menuSet += 1; 
        if(menuSet > 4 )menuSet = 1;
        }
      if(touchUp(Button_UP)){
        menuSet -= 1;
        if(menuSet < 1 )menuSet = 4;
        }
      if (menuSet == 1) {

        if (touchUp(Button_PLUS)) {
          modeMPU++; if(modeMPU>1)modeMPU = 0 ;
        }
        if (touchUp(Button_MIN)) {
          modeMPU--; if(modeMPU>0)modeMPU = 1 ;
        }        
        lcd.fillRect(0, 14, 128, 13, SH110X_WHITE);
        lcd_char(1, 2, 15, "MPU  : " + String(set[modeMPU]), false, false, false);
      } else {
        lcd_char(1, 2, 15, "MPU  : " + String(set[modeMPU]), true, false, false);
      }

      if (menuSet == 2) {
        if (touchUp(Button_PLUS)) {
          modeENC++; if(modeENC>1)modeENC = 0 ;
        }
        if (touchUp(Button_MIN)) {
          modeENC--; if(modeENC>0)modeENC = 1 ;
        }        
        lcd.fillRect(0, 24, 128, 13, SH110X_WHITE);
        lcd_char(1, 2, 27, "ENC  : " + String(set[modeENC]) , false, false, false);
      } else {
        lcd_char(1, 2, 27, "ENC  : " + String(set[modeENC]) , true, false, false);
      }


      if (menuSet == 3) {
        if (touchUp(Button_PLUS)) {
          modeWIFI++; if(modeWIFI>1)modeWIFI = 0 ;
        }
        if (touchUp(Button_MIN)) {
          modeWIFI--; if(modeWIFI>0)modeWIFI = 1 ;
        }        
        if(!modeWIFI){  
        lcd.fillRect(0, 34, 128, 13, SH110X_WHITE);
        lcd_char(1, 2, 37, "Wi-Fi: " + String(set[modeWIFI]), false, false, false); //pr con_wifi
        
        }else{
        lcd.fillRect(0, 34, 128, 13, SH110X_WHITE);
        lcd_char(1, 2, 37, "Wi-Fi: " + String(set[modeWIFI]) + "(" + String(set_wifi[conWifi]) + ")", false, false, false); //pr con_wifi
        }
      } else {
        if(!modeWIFI){  
        lcd_char(1, 2, 37, "Wi-Fi: " + String(set[modeWIFI]), true, false, false); //pr con_wifi
        }
        else{
        lcd_char(1, 2, 37, "Wi-Fi: " + String(set[modeWIFI]) + "(" + String(set_wifi[conWifi]) + ")", true, false, false); //pr con_wifi
        }
       
       }

      if (menuSet == 4) {
        if (touchUp(Button_PLUS)) {
          modeLF++; if(modeLF>1)modeLF = 0 ;
        }
        if (touchUp(Button_MIN)) {
          modeLF--; if(modeLF>0)modeLF = 1 ;
        }        
        lcd.fillRect(0, 44, 128, 13, SH110X_WHITE);
        lcd_char(1, 2, 47, "MODE : " + String(mode_lf[modeLF]), false, false, false);
      } else {
        lcd_char(1, 2, 47, "MODE : " + String(mode_lf[modeLF]), true, false, false);
      }
      lcd.display();
      }//end while
      

}




