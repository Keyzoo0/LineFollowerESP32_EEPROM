
void guiTunePid() {
  selectSet = 1;
  selectPresetPID = 0;
  int selectFLMODETest = 0;
  maxS = normalSpeed;
  readPID();
  while (1) {
    headUp(true, false);
    if (touchUp(Button_RUN)) {
      // savePID();
      lcd.clearDisplay();
      delay(50);
      break;
    }
    if (touchUp(Button_DOWN)) {
      selectSet++;
      if (selectSet > 6) selectSet = 1;
    }
    if (touchUp(Button_UP)) {
      selectSet--;
      if (selectSet < 1) selectSet = 6;
    }
    
    if (selectSet == 1) {
      lcd.drawRoundRect(18, 13, 81, 12, 3, SH110X_WHITE);
      if (touchUp(Button_PLUS)) {
        selectPresetPID++;
        if(selectPresetPID > 6) selectPresetPID = 0;
        }
      if (touchUp(Button_MIN)) {
        selectPresetPID--;
        if(selectPresetPID == 255) selectPresetPID = 6;
      }
    }
    if (selectSet == 2) {
      lcd.drawRoundRect(3, 28, 60, 12, 3, SH110X_WHITE);
      if (touchDown(Button_PLUS,50)){
        Kp[selectPresetPID] += 0.1;
        savePID();
      }
      if (touchDown(Button_MIN,50)){
        Kp[selectPresetPID] -= 0.1;
        savePID();
      }
    }
    if (selectSet == 3) {
      lcd.drawRoundRect(63, 28, 60, 12, 3, SH110X_WHITE);
      if (touchDown(Button_PLUS,50)){
        Kd[selectPresetPID] += 1.0;
        savePID();
      }
      if (touchDown(Button_MIN,50)){
        Kd[selectPresetPID] -= 1.0;
        savePID();
      }
    }
    if (selectSet == 4) {
      lcd.drawRoundRect(4, 39, 70, 12, 3, SH110X_WHITE);
      if (touchDown(Button_PLUS,50)){
        Ki[selectPresetPID] += 0.01;
        savePID();
      }
      if (touchDown(Button_MIN,50)){
        Ki[selectPresetPID] -= 0.01;
        savePID();
      }    }
    if (selectSet == 5){
      lcd.drawRoundRect(74, 39, 50, 12, 3, SH110X_WHITE);
      if (touchUp(Button_PLUS)) {
        selectFLMODETest++;
        if(selectFLMODETest > 2) selectFLMODETest = 0;
      }
      if (touchUp(Button_MIN)) {
        selectFLMODETest--;
        if(selectFLMODETest < 0) selectFLMODETest = 2;
      }
    }
    if (selectSet == 6) {
      lcd.drawRoundRect(30, 50, 56, 12, 3, SH110X_WHITE);
      if (touchUp(Button_OK)) {
        oledClear();
        if(dumpBat > 11.8){
        oledClear();
        selectPresetPIDPlay = selectPresetPID;
        while (1) {
          
          int bufDataSensor = readSensor();
          headUp(true, false);
          dispSensor(bufDataSensor);
            program(bufDataSensor, selectFLMODETest , normalSpeed , selectPresetPID ) ;
          if (touchUp(Button_RUN)) {
            oledClear();
            selectSet = 1;
            selectPresetPIDPlay = 0;
            stopMotor();
            break;
            readSens = false ;
          }
          lcd.display();
        }// while 

        }else{
          lcd_char(2 , 20 , 0, "BATERRY" , true , true , true);
          lcd_char(2 , 35 , 30, "LOW!!" , true , false, true);
          delay(1000);
          lcd.clearDisplay();
        }
      }
    }
    lcd_char(1, 20, 15, "Preset:" + (String)slctPID[selectPresetPID], true, false, false);
    lcd_char(1, 5, 30, "Kp: " + String(Kp[selectPresetPID], 2), true, false, false);
    lcd_char(1, 65, 30, "Kd: " + String(Kd[selectPresetPID], 2), true, false, false);
    sprintf(buff , "Ki : %1.3f" , Ki[selectPresetPID]);
    lcd_char(1, 5, 42, buff, true, false, false);
    lcd_char(1, 76, 42, "FL :" + String(slctFLMODE[selectFLMODETest]), true, false, false);
    lcd_char(1, 33, 53, "Coba PID", true, false, false);
    lcd.display();
  }
}

// void guiTunePid() { 
//   byte menuPid = 0 , profil = 0;
//   readPID();
//   while (1) {
//     headUp(true, false);
//     if (touchUp(btnBack)) {
//       lcd.clearDisplay();
//       savePID();
//       break;
//     }
//     if (touchUp(btnDown)) {
//       menuPid++;
//       if (menuPid > 3) menuPid = 0;
//     }
//     if (touchUp(btnUp)) {
//       menuPid--;
//       if (menuPid == 255) menuPid = 3;
//     }

//     if (touchUp(Button_OK)) {
//     oledClear();
//     selectSet = 1;
//     selectPresetPID = profil;
//   int selectFLMODETest = 0;
//     while (1) {
//       int bufDataSensor = readSensor();
//       headUp(true, false);
//       dispSensor(bufDataSensor);
//       program(bufDataSensor, "center");
//       if (touchUp(Button_RUN)) {
//         oledClear();
//         selectSet = 1;
//         selectPresetPIDPlay = 0;
//         stopMotor();
//         break;
//       }
//       lcd.display();
//     }
//   }

//     sprintf(buff, " Profil:%s", String(slctPID[profil]));
//     lcd_char(1, 2, 15, buff, true, false, false);
//     sprintf(buff, " KP:%2.0f", Kp[profil]);
//     lcd_char(1, 2, 25, buff, true, false, false);
//     sprintf(buff, " KI:%1.2f", Ki[profil] );
//     lcd_char(1, 2, 35, buff, true, false, false);
//     sprintf(buff, " KD:%1.1f", Kd[profil] );
//     lcd_char(1, 2, 45, buff, true, false, false);

//     if (menuPid == 0) {
//       if (touchDown(btnPlus,200)) {
//         profil++;
//         if (profil > 6) profil = 0;
//       }
//       if (touchDown(btnMinus,200)) {    
//         profil--;
//         if (profil == 255) profil = 6;
//       }
//       lcd_char(1, 0, 15, ">", true, false, false);

//     }

//     if (menuPid == 1) {
//       if (touchDown(btnPlus,200)) {    
//         Kp[profil]+=1.0;
//         if (Kp[profil] > 20) Kp[profil] = 0;
//         savePID();
//       }
//       if (touchDown(btnMinus,200)) {
//         Kp[profil]-=1.0;
//         if (Kp[profil] < 0) Kp[profil] = 20;
//         savePID();
//       }
//       lcd_char(1, 0, 25, ">", true, false, false);
//     }
//     if (menuPid == 2) {
//       if (touchDown(btnPlus,200)) {
        
//         Ki[profil]+= 0.01;
//         if (Ki[profil] > 1) Ki[profil] = 0;
//         savePID();
//       }
//       if (touchDown(btnMinus,200)) {
        
//         Ki[profil]-=0.01;
//         if (Ki[profil] < 0.01 ) Ki[profil] = 1;
//         savePID();
//       }
//       lcd_char(1, 0, 35, ">", true, false, false);
//     }
//     if (menuPid == 3) {
//       if (touchDown(btnPlus,200)) {
//         Kd[profil]+=0.1;
//         if (Kd[profil] > 10) Kd[profil] = 0;
//       }
//       if (touchDown(btnMinus,200)) {
//         Kd[profil]-=0.1;
//         if (Kd[profil] < 0) Kd[profil] = 10;
//         savePID();
//       }
//       lcd_char(1, 0, 45, ">", true, false, false);
//     }
//     lcd.display();
//   }
// }
