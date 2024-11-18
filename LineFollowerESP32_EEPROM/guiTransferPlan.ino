void guiTransferPlan(){
  oledClear();
  while(1){
      // (55, 25, 38, 10, 2, SH110X_WHITE);
      // (1, 57, 26, "Manual", true, false, false);
      lcd.drawRoundRect(8, 19, 50, 12, 3, SH110X_WHITE);
      lcd_char(1, 12, 20, "Receive", true, false, false);
      lcd.drawRoundRect(65, 19, 50, 12, 3, SH110X_WHITE);
      lcd_char(1, 67, 20, "Transmit", true, false, false);
      lcd.display();
    if(touchUp(Button_RUN)){
      break;
    }
    if(touchUp(Button_UP)){
      guiReceive();
    }
    if(touchUp(Button_PLUS)){
      guiTransmit();
    } 

  }
}

void guiReceive(){
  oledClear();
  while(1){
    if(touchUp(Button_RUN)){
      oledClear();
      break;
    }
    lcd_char(1, 12, 20, "Lagi Recieve Bang !", true, false, false);
    lcd.display();
  }
}

void guiTransmit(){
  oledClear();
  while(1){
    if(touchUp(Button_RUN)){
      oledClear();
      break;
    }
    lcd_char(1, 12, 20, "Lagi Transmit Bang !", true, false, false);
    lcd.display();

  }
}
  