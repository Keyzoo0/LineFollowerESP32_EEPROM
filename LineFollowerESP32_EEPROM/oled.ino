void initDisplay() {
  lcd.setRotation(2);
  lcd.begin(OLED_ADDR, true);
  lcd.clearDisplay();
  lcd.drawBitmap(0, 0, Logo_EEPROM, 128, 64, SH110X_WHITE);
  lcd_char(1, 46, 56, "EEPROM", true, false, true);
  lcd.cp437(true);
  delay(500);
}

void lcd_char(int size, int x, int y, String text, bool warna, bool clear, bool display) {
  if (clear)lcd.clearDisplay();
  if (warna)lcd.setTextColor(SH110X_WHITE);
  else lcd.setTextColor(SH110X_BLACK);
  lcd.setTextSize(size);
  lcd.setCursor(x, y);
  lcd.print(text);
  if (display)lcd.display();
}

void oledClear()
{
  lcd.clearDisplay();
  lcd.display();
}

void dispSensor(unsigned int sens) {
  //  int sens = readSensor();
  for (int i = 0; i < 14; i++) {
    if ((sens << i) & 0b10000000000000) {
      lcd.fillRect(17 + (7 * i), 15, 5, 13, SH110X_WHITE);
    } else {
      lcd.fillRect(17 + (7 * i), 15, 5, 13, SH110X_BLACK);
      lcd.fillRect(17 + (7 * i), 15 + 13 - 1, 5, 1, SH110X_WHITE);
    }
  }
}

void dispSensorIdx(unsigned int sens) {
  //  int sens = readSensor();
  for (int i = 0; i < 14; i++) {
    if ((sens << i) & 0b10000000000000) {
      lcd.fillRect(28 + (6 * i), 24, 3, 13, SH110X_WHITE);
    } else {
      lcd.fillRect(28 + (6 * i), 24, 3, 13, SH110X_BLACK);
      lcd.fillRect(28 + (6 * i), 24 + 13 - 1, 3, 1, SH110X_WHITE);
    }
  }
}

unsigned long prevTimeHead;
float dumpBat;

void headUp(bool clr , bool show) {
  if (clr) lcd.clearDisplay();
  if (millis() - prevTimeHead >= 1000) {
    dumpBat = readBattery();
    prevTimeHead = millis();
  }
  sprintf(buff, "%02.1fV", dumpBat);
  lcd_char(1, 1, 1, buff, true, false, false);
  lcd_char(1, 60, 1, "EEPROM G13", true, false, false);
  lcd.drawLine(0, 12, 128, 12, SH110X_WHITE);
  if (show)lcd.display();
}

void headUpIdx(bool clr , bool show) {
  if (clr) lcd.clearDisplay();
  sprintf(buff, "Set P:%d-Idx:%02d", plan + 1, countIdx);
  lcd_char(1, 1, 1, buff, true, false, false);
  lcd_char(1, 100, 1, " G13", true, false, false);
  lcd.drawLine(0, 12, 128, 12, SH110X_WHITE);
  if (show)lcd.display();
}

void lcd_loading(int x, int y, int progress, bool text, bool clear, bool display) {
  float bar = ((float)(110 - 1) / 100) * progress;
  if (clear)lcd.clearDisplay();
  if (text)lcd_char(1, 10, y-10, "LOADING...", true, false, false);
  lcd.drawRoundRect(x, y, 110, 8, 3, SH110X_WHITE);
  lcd.fillRoundRect(x + 2, y + 2, bar, 4, 1, SH110X_WHITE);
  if (display)lcd.display();
}

void clearBuffer() {
  for (uint8_t i = 0; i < 100; i++) {
    buff[i] = 0;
  }
}
