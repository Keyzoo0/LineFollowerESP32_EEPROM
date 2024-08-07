
void setup() {
//setup robot
  Serial.begin(115200);
  setCpuFrequencyMhz(240);
  initDisplay();
  memory.begin();
  setupPID();
  initTimer();
  initEncoder(1);
  setupSensor();
  initMotor();
  initButton();
//read data 
  readCalib();
  readHome();
  read_PID();
  readIdx();
  readMaxMinSens();
  readCP();
  readSensorSens();
  delay(500);
  oledClear();


}

void loop() {
  stopMotor();
homeSC:
  initEncoder(false);
  while (homeS) {
    headUp(true, false);
    dispSensor(readSensor());
    if (touchUp(Button_DOWN)) {
      menuHome++;
      if (menuHome > 5) menuHome = 1;
    }
    if (touchUp(Button_UP)) {
      menuHome--;
      if (menuHome == 255) menuHome = 5;
    }
    if (touchUp(Button_RUN)) {
      oledClear();
      stateRun = true;
      homeS = false;
      break;
    }

    if (menuHome == 1) {
      if (touchUp(Button_PLUS)) {
        plan++;
        if (plan > 4) plan = 0;
      }
      if (touchUp(Button_MIN)) {
        plan--;
        if (plan < 0) plan = 4;

        if (plan == 255) plan = 0;
      }

      lcd.fillRoundRect(32, 0, 23, 10, 3, SH110X_WHITE);
      sprintf(buff, "P:%d", plan + 1);
      lcd_char(1, 36, 2, buff, false, false, false);
    } else {
      lcd.drawRoundRect(32, 0, 23, 10, 3, SH110X_WHITE);
      sprintf(buff, "P:%d", plan + 1);
      lcd_char(1, 36, 2, buff, true, false, false);
    }

    if (menuHome == 3) {
      if (touchUp(Button_PLUS)) {
        countCP++;
        if (countCP > 8)  countCP = 0;
      }
      if (touchUp(Button_MIN)) {
        countCP--;
        if (countCP <0)  countCP = 8;

        if (countCP == 255) countCP = 0;
      }
      if(touchUp(Button_OK)){
        oledClear();
        selectSet = 0;
        menuCheckpoint();
      }
      lcd.fillRoundRect(0, 46, 30, 15, 3,  SH110X_WHITE);
      sprintf(buff, "CP:%01d", countCP);
      lcd_char(1, 2, 51, buff, false, false, false);
    } else {
      lcd.drawRoundRect(0, 46, 30, 15, 3,  SH110X_WHITE);
      sprintf(buff, "CP:%01d", countCP);
      lcd_char(1, 2, 51, buff, true, false, false);
    }

    if (menuHome == 4) {
      if (touchDown(Button_PLUS , 100)) {
        stopIndex++;
        if (stopIndex > 100) stopIndex = 0;
        delay(10);
      }
      if (touchDown(Button_MIN, 100)) {
        stopIndex--;
        if (stopIndex < 0) stopIndex = 100;
        if (plan == 255) plan = 0;
        delay(10);
      }
      lcd.fillRoundRect(32, 46, 52, 15, 3,  SH110X_WHITE);
      sprintf(buff, "STOP:%03d", stopIndex);
      lcd_char(1, 34, 51, buff, false, false, false);
    } else {
      lcd.drawRoundRect(32, 46, 52, 15, 3,  SH110X_WHITE);
      sprintf(buff, "STOP:%03d", stopIndex);
      lcd_char(1, 34, 51, buff, true, false, false);
    }

    if (menuHome == 2) {
      if (touchDown(Button_PLUS , 50)) {
        normalSpeed += 5;
        if (normalSpeed >= 255) normalSpeed = 0;
      }
      if (touchDown(Button_MIN , 50 )) {
        normalSpeed -= 5;
        if (normalSpeed <= 0) normalSpeed = 255;
      }
      lcd.fillRoundRect(48, 30, 35, 15, 3,  SH110X_WHITE);
      sprintf(buff, "N:%03d", normalSpeed);
      lcd_char(1, 51, 34, buff, false, false, false);
    } else {
      lcd.drawRoundRect(48, 30, 35, 15, 3,  SH110X_WHITE);
      sprintf(buff, "N:%03d", normalSpeed);
      lcd_char(1, 51, 34, buff, true, false, false);
    }

    if (menuHome == 5) {
      if (touchUp(Button_OK)) {
        lcd.clearDisplay();
        menu();
      }
      lcd.fillRoundRect(90, 46, 35, 15, 3,  SH110X_WHITE);
      lcd_char(1, 96, 51, "MENU", false, false, false);
    } else {
      lcd.drawRoundRect(90, 46, 35, 15, 3,  SH110X_WHITE);
      lcd_char(1, 96, 51, "MENU", true, false, false);
    }
    lcd.display();
  } // end bracket While true

  if (stateRun) {
    if(countCP != 0){
        readCounter(readCCheckpoint[plan][countCP]);
        countIdxPlay = readIdxCheckpoint[plan][countCP];
    }
    while (1) {
      dataSensor = readSensor();
      sensLogPlay = sensLog[sensLogIdx[plan][countIdxPlay]];
      selectPresetPIDPlay = pidProfile[plan][countIdxPlay];
      clrLine[plan][countIdxPlay] == 0 ? clrLinePlay = false : clrLinePlay = true;

      switch (logic[plan][countIdxPlay]) {
        case 0: // Or
//          dataSensor = readSensor();
          if (clrLinePlay) {
            while(1){
              maxS = normalSpeed;
              program(readSensor(), "center");
              if (~(readSensor()) & sensLogPlay) {
                SLED(1);
                playAction = true;
                break;
              }
            }
          } else {
            while(1){
              maxS = normalSpeed;
              program(readSensor(), "center");
              if (readSensor() & sensLogPlay) {
                SLED(1);
                playAction = true;
                break;
              }
            }
          }
          break;

        case 1: // And
//          dataSensor = readSensor();
          if (clrLinePlay) {
            while(1){
              maxS = normalSpeed;
              program(readSensor(), "center");
              if ((~(readSensor()) & sensLogPlay) == sensLogPlay) {
                SLED(1);
                playAction = true;
                break;
              }
            }
          } else {
            while(1){
              maxS = normalSpeed;
              program(readSensor(), "center");
              if ((readSensor() & sensLogPlay) == sensLogPlay) {
               SLED(1);
               playAction = true;
               break;
              }
            }
          }
          break;

        case 2: // TIM
          dataSensor = readSensor();
          SLED(1);
          playAction = true;
          maxS = normalSpeed;
          break;

        case 3: // XOR
          dataSensor = readSensor();
          if (clrLinePlay) {
            byte logSen = sensLogIdx[plan][countIdxPlay];
            if (logSen == 16) {
              if (~(dataSensor) & 0b00000111100000) {
                if (~(dataSensor) & 0b10000000000000) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
            else if (logSen == 17) {
              if (~(dataSensor) & 0b00000111100000) {
                if (~(dataSensor) & 0b00000000000001) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
            else if (logSen == 18) {
              if (~(dataSensor) & 0b00000111100000) {
                if (~(dataSensor) & 0b11000000000000) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
            else if (logSen == 19) {
              if (~(dataSensor) & 0b00000111100000) {
                if (~(dataSensor) & 0b00000000000011) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
          } else {
            byte logSen = sensLogIdx[plan][countIdxPlay];
            if (logSen == 16) {
              if (dataSensor & 0b00000111100000) {
                if (dataSensor & 0b10000000000000) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
            else if (logSen == 17) {
              if (dataSensor & 0b00000111100000) {
                if (dataSensor & 0b00000000000001) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
            else if (logSen == 18) {
              if (dataSensor & 0b00000111100000) {
                if (dataSensor & 0b11000000000000) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
            else if (logSen == 19) {
              if (dataSensor & 0b00000111100000) {
                if (dataSensor & 0b00000000000011) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
          }
          break;
      }

      if (playAction) { 
        readCounter(idx[plan][countIdxPlay]);
        dataSensor = readSensor();
        SLED(0);
        TA = timerA[plan][countIdxPlay];
        timerSpeedA = speedA[plan][countIdxPlay];
        int16_t sTA = timerSpeedA / 4;
        lastTimeIdxTA = timeIdxTA;
        countEnc_B = countEnc_A = 0;
        initEncoder(true);
        while (1) {
          if (speedA[plan][countIdxPlay] == 0) {
            maxS = 0;
            stopMotor();
          }
          else if (sTA < speedA[plan][countIdxPlay]) {
            sTA += 2;
            if (sTA < 40) maxS = 40;
            else if (sTA >= speedA[plan][countIdxPlay]) maxS = speedA[plan][countIdxPlay];
            else maxS = sTA;
          }
          program(readSensor(), "center");
          if(modeTIM[plan][countIdxPlay] == 0){
            if (timeIdxTA - lastTimeIdxTA >= TA) break;
          }
          if(modeTIM[plan][countIdxPlay] == 1){
            if(measureLengthR() >= TA) break;
          }
          if(modeTIM[plan][countIdxPlay] == 2){
            if(measureLengthL() >= TA) break;
          }
        }

        TB = timerB[plan][countIdxPlay];
        timerSpeedB = speedB[plan][countIdxPlay];
        int16_t sTB = timerSpeedB / 4;
        lastTimeIdxTB = timeIdxTB;
        while (1) {
          if (speedB[plan][countIdxPlay] == 0) {
            maxS = 0;
            stopMotor();
          }
          else if (timerA[plan][countIdxPlay] == 0) {
            sTB += 2;
            if (sTB < 40) maxS = 40;
            else maxS = sTB;
            if (sTB >= speedB[plan][countIdxPlay]) maxS = speedB[plan][countIdxPlay];
          } else if ( speedB[plan][countIdxPlay] > speedA[plan][countIdxPlay]) {
            timerSpeedA += 2;
            maxS = timerSpeedA;
            if ( timerSpeedA > speedB[plan][countIdxPlay]) maxS = speedB[plan][countIdxPlay];
          } else if ( speedB[plan][countIdxPlay] < speedA[plan][countIdxPlay]) {
            timerSpeedA -= 3;
            maxS = timerSpeedA;
            if ( timerSpeedA <= speedB[plan][countIdxPlay]) maxS = speedB[plan][countIdxPlay];
          }
          program(readSensor(), "center");
          if (timeIdxTB - lastTimeIdxTB >= TB) break;
        }

        if (countIdxPlay > stopIndex) {
          TA = TB = maxS = 0;
          stopMotor();
        } else if (touchUp(Button_OK)){
          TA = TB = countIdxPlay = 0;
          break;
        }
        playAction = false;
      } // end bracket playAction
      TA = TB = 0;
      countIdxPlay++;

      if (countIdxPlay > stopIndex) {
        stopMotor();
        TA = TB = maxS = countIdxPlay = 0;
        stateRun = playAction = false;
        homeS = true;
        break;
        goto homeSC;
      }

      if (touchUp(Button_OK)) {
        TA = TB = maxS = countIdxPlay = 0;
        stateRun = playAction = false;
        homeS = true;
        stopMotor();
        break;
        goto homeSC;
      }
    } // end while bracket
  } // if stateRun

} // end void loop

