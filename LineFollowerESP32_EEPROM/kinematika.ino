
void chkPnt() {
  slct = countCP;
  stopCount = stopIndex;

  while (1) {
    headUp(true, false);
    sprintf(buff, " Plan:%d      Start:%02d", plan + 1, readIdxCheckpoint[plan][slct]);
    lcd_char(1, 2, 15, buff, true, false, false);
    sprintf(buff, " Read CP:%02d  Stop:%02d", slct, stopCount);
    lcd_char(1, 2, 30, buff, true, false, false);
    lcd.fillRoundRect(48, 47, 29, 13, 3, SH110X_WHITE);
    lcd_char(1, 51, 50, "EEOS", false, false, false);

    if (touchDown(btnDown,50) ) {
  
      slct--;
      if (slct == 255) slct = VAL_CHECKP;
      countCP = slct ;
      saveHome();   }
    if (touchDown(btnUp,50) ) {
  
      slct++;
      if (slct > VAL_CHECKP) slct = 0;
      countCP = slct ;
      saveHome();
    }
    if (touchDown(btnPlus,50) ) {
  
      stopCount++;
      if (stopCount > 99 ) stopCount = 0;
      stopIndex = stopCount ;
      saveHome();
    }
    if (touchDown(btnMinus,50) ) {
  
      stopCount--;
      if (stopCount == 255) stopCount = 99;
      stopIndex = stopCount ;
      saveHome();
    }
    if (touchUp(btnBack) ) {
  
      if (slct > 0) {
        start = CP[plan].saveReadIdx[slct];
        protec = true;
        break;
      }
      else {
        start = 0;
        protec = false;
        break;
      }
    }
    lcd.display();
  }
}

void read_counter() {
  counting = Plan[plan].saveIdx[start];
  if (counting == 0) {
    stop();
  }
  else if (counting == 1) {
    forward();
  }
  else if (counting == 2) {
    left();
  }
  else if (counting == 3) {
    right();
  }
  else if (counting == 4) {
    backward();
  }
  else if (counting == 5) {
    pick();
  }
  else if (counting == 6) {
    drop();
  }
  else if (counting == 7) {
    turnLeft();
  }
  else if (counting == 8) {
    turnRight();
  }
}


void stop() {
  stopMotor();
  delay(((Plan[plan].saveidelayH[start]<<8) | Plan[plan].saveidelayL[start]) * 15);
}

void forward(void) {
  int sped;
  int spedN = 50;
  timeTrig = millis();
  if (start == 0) sped = normalSpeed;
  while (1) {
    if (spedN < sped) {
      spedN += 2;
      if (spedN < 50) sped = 50;
      else sped = spedN;
      if (spedN >= sped) sped = sped;
    }
    pwmMotor(sped, sped);

    if ((millis()  - timeTrig) > (Plan[plan].saveidelayH[start]<<8)|Plan[plan].saveidelayL[start])  break;
  
  }
  timeTrig = 0;
}
void backward(void) {
  // LED(true);
  // stopMotor();
  // delay(200);
  // pwmMotor(Plan[plan].spdR[start] * -1, Plan[plan].spdR[start] * -1);
  // delay(Plan[plan].edelay[start] * 15);
  // stopMotor();
  // delay(200);
}
void right(void) {
  // LED(true);
  // pwmMotor(Plan[plan].spdR[start], Plan[plan].spdL[start] * -1);
  // delay(Plan[plan].edelay[start] * 2);
}
void left(void) {
  // LED(true);
  // pwmMotor(Plan[plan].spdL[start] * -1, Plan[plan].spdR[start]);
  // delay(Plan[plan].edelay[start] * 2);
}
void pick() {
  // stopMotor();
  // //Lengan.write(turun);
  // delay(Plan[plan].edelay[start] * 8);
  // //Capit.write(capit);
  // delay(Plan[plan].edelay[start] * 8);
  // //Lengan.write(naik);
  // delay(Plan[plan].edelay[start] * 8);
}
void drop() {
  // LED(true);
  // stopMotor();
  // //Lengan.write(turun);
  // delay(Plan[plan].edelay[start] * 8);
  // //Capit.write(lepas);
  // delay(Plan[plan].edelay[start] * 8);
  // //Lengan.write(naik);
  // delay(Plan[plan].edelay[start] * 8);
}
void turnRight(void) {
  // int dataSensor;
  // pwmMotor(200, -200);
  // delay(100);
  // while (1) {
  //   if (invers) {
  //     dataSensor = readSensor();
  //     LED(true);
  //     if (dataSensor & 0b00000011000000) {
  //       break;
  //     }
  //     else {
  //       pwmMotor(200, -200);
  //     }
  //   } else {
  //     dataSensor = readSensor();
  //     LED(true);
  //     if (~(dataSensor) & 0b00000011000000) {
  //       break;
  //     }
  //     else {
  //       pwmMotor(200, -200);
  //     }
  //   }
  // }
}
void turnLeft(void) {
  // int dataSensor;
  // pwmMotor(-200, 200);
  // delay(100);
  // while (1) {
  //   if (invers) {
  //     dataSensor = readSensor();
  //     LED(true);
  //     if (dataSensor & 0b00000011000000) {
  //       break;
  //     }
  //     else {
  //       pwmMotor(-200, 200);
  //     }
  //   } else {
  //     dataSensor = readSensor();
  //     LED(true);
  //     if (~(dataSensor) & 0b00000011000000) {
  //       break;
  //     }
  //     else {
  //       pwmMotor(-200, 200);
  //     }
  //   }
  // }
}

void servoStanby() {
  // LED(true);
  // stopMotor();
  // //Lengan.write(turun);
  // delay(Plan[plan].edelay[start] * 8);
  // //Capit.write(lepas);
  // delay(Plan[plan].edelay[start] * 8);
  // //Lengan.write(naik);
  // delay(Plan[plan].edelay[start] * 8);
}


