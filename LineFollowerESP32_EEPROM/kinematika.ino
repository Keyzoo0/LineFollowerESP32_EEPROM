
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
  counting = idx[plan][start];
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
  else if (counting == 9) {
    fan();
  }
}
void fan(){
  stopMotor();
  delay(idelay[plan][start] * 15);

}

void stop() {
  stopMotor();
  delay(idelay[plan][start]* 15);
}

void forward(void) {

  timeTrig = millis();
  while (1) {
    
    pwmMotor(spdL[plan][start], spdR[plan][start]);

    if ((millis()  - timeTrig) >= idelay[plan][start]*10)  break;
  
  }
  timeTrig = 0;
}
void backward(void) {
  timeTrig = millis();
  while (1) {
    
    pwmMotor(spdL[plan][start] * -1 , spdR[plan][start] * -1);
    if ((millis()  - timeTrig) >= idelay[plan][start]*10)  break;
  
  }
  timeTrig = 0;
}
void right(void) {
  pwmMotor(spdL[plan][start], spdR[plan][start] * -1);
  delay(idelay[plan][start] * 4);
}
void left(void) {
  pwmMotor(spdL[plan][start] * -1, spdR[plan][start]);
  delay(idelay[plan][start] * 4);
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
  pwmMotor(200, -200);
  delay(idelay[plan][start] * 4);
}
void turnLeft(void) {
  
  pwmMotor(-200,200);
  delay(idelay[plan][start] * 4);

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


