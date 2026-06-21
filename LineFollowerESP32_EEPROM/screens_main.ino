// ===========================================================================
// Layar: Home, Main Menu, Settings, Throttle, Set Default, Race Result.
// Semua non-blocking: handleX() = logika, renderX() = gambar (1 frame).
// ===========================================================================

//================================ HOME ==================================
void handleHome() {
  if (btnPressed(BTN_UP))   { if (--stHome.sel < 0) stHome.sel = 4; }
  if (btnPressed(BTN_DOWN)) { if (++stHome.sel > 4) stHome.sel = 0; }

  switch (stHome.sel) {
    case 0: // mode C(race) / F(tune)
      if (btnPressed(BTN_PLUS)) stHome.race = true;
      if (btnPressed(BTN_MIN))  stHome.race = false;
      if (btnPressed(BTN_OK))   pushScreen(SCR_MENU);
      break;
    case 1: // pilih plan
      if (btnRepeat(BTN_PLUS)) { if (++plan >= VAL_PLAN) plan = 0; saveHome(); }
      if (btnRepeat(BTN_MIN))  { plan = (plan == 0) ? VAL_PLAN - 1 : plan - 1; saveHome(); }
      if (btnPressed(BTN_OK))  pushScreen(SCR_SETINDEX);
      break;
    case 2: // normal speed
      if (btnRepeat(BTN_PLUS)) { if (normalSpeed <= 250) normalSpeed += 5; saveHome(); }
      if (btnRepeat(BTN_MIN))  { if (normalSpeed >= 5)   normalSpeed -= 5; saveHome(); }
      break;
    case 3: if (btnPressed(BTN_OK)) pushScreen(SCR_CHECKPOINT); break;
    case 4: if (btnPressed(BTN_OK)) pushScreen(SCR_CALIB);      break;
  }

  if (btnPressed(BTN_BACK)) {              // RUN = mulai
    if (stHome.race) { if (readBattery() >= minBat) runRace(); }
    else             pushScreen(SCR_TUNEPID);
  }
}

void renderHome() {
  headUp(false, false);
  displaySensor(readSensor());

  // Mode C/F
  if (stHome.sel == 0) lcd.fillRoundRect(48, 30, 30, 30, 5, SH110X_WHITE);
  else                 lcd.drawRoundRect(48, 30, 30, 30, 5, SH110X_WHITE);
  lcd_char(3, 56, 35, stHome.race ? "C" : "F", stHome.sel != 0, false, false);

  // SetP
  if (stHome.sel == 1) lcd.fillRoundRect(-5, 27, 45, 20, 3, SH110X_WHITE);
  else                 lcd.drawRoundRect(-5, 27, 45, 20, 3, SH110X_WHITE);
  sprintf(buff, "SetP:%d", plan + 1);
  lcd_char(1, 1, 31, buff, stHome.sel != 1, false, false);

  // Ns
  if (stHome.sel == 2) lcd.fillRoundRect(-5, 42, 45, 20, 3, SH110X_WHITE);
  else                 lcd.drawRoundRect(-5, 42, 45, 20, 3, SH110X_WHITE);
  sprintf(buff, "Ns:%03d", normalSpeed);
  lcd_char(1, 1, 51, buff, stHome.sel != 2, false, false);

  // CALSEN
  if (stHome.sel == 4) lcd.fillRoundRect(87, 27, 45, 20, 3, SH110X_WHITE);
  else                 lcd.drawRoundRect(87, 27, 45, 20, 3, SH110X_WHITE);
  lcd_char(1, 90, 31, "CALSEN", stHome.sel != 4, false, false);

  // CHKPNT
  if (stHome.sel == 3) lcd.fillRoundRect(87, 42, 45, 20, 3, SH110X_WHITE);
  else                 lcd.drawRoundRect(87, 42, 45, 20, 3, SH110X_WHITE);
  lcd_char(1, 90, 51, "CHKPNT", stHome.sel != 3, false, false);
}

//================================ MENU ==================================
// 0 Set Plan · 1 Calib · 2 Tune PID · 3 Test Motor · 4 Copy/Mirror · 5 Delete · 6 Settings
void handleMenu() {
  if (btnPressed(BTN_UP))   { if (--stMenu.sel < 0) stMenu.sel = 6; }
  if (btnPressed(BTN_DOWN)) { if (++stMenu.sel > 6) stMenu.sel = 0; }
  if (btnPressed(BTN_BACK)) { saveAll(); popScreen(); return; }

  switch (stMenu.sel) {
    case 0:
      if (btnRepeat(BTN_PLUS)) { if (++plan >= VAL_PLAN) plan = 0; }
      if (btnRepeat(BTN_MIN))  { plan = (plan == 0) ? VAL_PLAN - 1 : plan - 1; }
      if (btnPressed(BTN_OK))  pushScreen(SCR_SETINDEX);
      break;
    case 1:
      if (btnPressed(BTN_PLUS)) pushScreen(SCR_CALIB_AUTO);
      if (btnPressed(BTN_MIN))  pushScreen(SCR_CALIB_MANUAL);
      break;
    case 2: if (btnPressed(BTN_OK)) pushScreen(SCR_TUNEPID);    break;
    case 3: if (btnPressed(BTN_OK)) pushScreen(SCR_TESTMOTOR);  break;
    case 4: if (btnPressed(BTN_OK)) pushScreen(SCR_COPYMIRROR); break;
    case 5:
      if (btnRepeat(BTN_PLUS)) { if (++plan >= VAL_PLAN) plan = 0; }
      if (btnRepeat(BTN_MIN))  { plan = (plan == 0) ? VAL_PLAN - 1 : plan - 1; }
      if (btnPressed(BTN_OK))  { stReset.target = plan; pushScreen(SCR_RESETPLAN); }
      break;
    case 6: if (btnPressed(BTN_OK)) pushScreen(SCR_SETTINGS); break;
  }
}

void renderMenu() {
  const char* titles[7] = { "Set Plan", "Calib Sensor", "Tuning PID",
                            "Test Motor", "Copy Mirror Plan", "Delete Plan", "Settings" };
  switch (stMenu.sel) {
    case 0: lcd.drawBitmap(0, 5, logoSetPlan,         128, 64, SH110X_WHITE); break;
    case 1: lcd.drawBitmap(0, 5, logoCalibSensor,     128, 64, SH110X_WHITE); break;
    case 2: lcd.drawBitmap(0, 0, logoTunePID,         128, 64, SH110X_WHITE); break;
    case 3: lcd.drawBitmap(0, 0, logoTestMotor,       128, 64, SH110X_WHITE); break;
    case 4: lcd.drawBitmap(0, 0, logoCopyMirrorPlan,  128, 64, SH110X_WHITE); break;
    case 5: lcd.drawBitmap(0, 0, logoDeletePlan,      128, 64, SH110X_WHITE); break;
    case 6: lcd.drawBitmap(0, 0, logoSettings,        128, 64, SH110X_WHITE); break;
  }
  lcd_char(1, 18, 5, titles[stMenu.sel], true, false, false);

  if (stMenu.sel == 0 || stMenu.sel == 5) { sprintf(buff, "P%d", plan + 1); lcd_char(3, 78, 25, buff, true, false, false); }
  if (stMenu.sel == 1) { lcd_char(1, 70, 28, "+:Auto", true, false, false); lcd_char(1, 70, 42, "-:Manual", true, false, false); }

  // scrollbar
  lcd.drawRoundRect(124, 0, 3, 56, 1, SH110X_WHITE);
  lcd.fillRoundRect(124, 2 + stMenu.sel * 7, 3, 6, 1, SH110X_WHITE);
}

//============================== SETTINGS ================================
// hanya fitur yang benar-benar jalan: Set Default & Set Throttle.
void handleSettings() {
  if (btnPressed(BTN_UP))   { if (--stSettings.sel < 0) stSettings.sel = 1; }
  if (btnPressed(BTN_DOWN)) { if (++stSettings.sel > 1) stSettings.sel = 0; }
  if (btnPressed(BTN_BACK)) { saveAll(); popScreen(); return; }
  if (btnPressed(BTN_OK)) {
    if (stSettings.sel == 0) pushScreen(SCR_SETDEFAULT);
    else                     pushScreen(SCR_THROTTLE);
  }
}

void renderSettings() {
  lcd_char(1, 25, 2, "SETTINGS", true, false, false);
  lcd.drawLine(0, 12, 128, 12, SH110X_WHITE);
  const char* items[2] = { "Set Default", "Set Throttle" };
  for (int i = 0; i < 2; i++) {
    if (i == stSettings.sel) { lcd.fillRoundRect(4, 20 + i * 16, 120, 13, 2, SH110X_WHITE);
                               lcd_char(1, 10, 23 + i * 16, items[i], false, false, false); }
    else                       lcd_char(1, 10, 23 + i * 16, items[i], true, false, false);
  }
}

//============================== THROTTLE ================================
void handleThrottle() {
  if (btnPressed(BTN_UP) || btnPressed(BTN_DOWN)) stThrottle.sel = !stThrottle.sel;
  if (stThrottle.sel == 0) {
    if (btnRepeat(BTN_PLUS)) { if (++accelTA > 25) accelTA = 1; }
    if (btnRepeat(BTN_MIN))  { if (--accelTA == 0) accelTA = 25; }
  } else {
    if (btnRepeat(BTN_PLUS)) { if (++accelTB > 25) accelTB = 1; }
    if (btnRepeat(BTN_MIN))  { if (--accelTB == 0) accelTB = 25; }
  }
  if (btnPressed(BTN_BACK)) { saveAccel(); popScreen(); return; }
}

void renderThrottle() {
  lcd_char(1, 5, 2, "Set Throttle", true, false, false);
  lcd.drawLine(0, 12, 128, 12, SH110X_WHITE);
  sprintf(buff, "AccTA: %2d", accelTA);
  if (stThrottle.sel == 0) { lcd.fillRoundRect(10, 22, 108, 14, 2, SH110X_WHITE); lcd_char(1, 16, 26, buff, false, false, false); }
  else                       lcd_char(1, 16, 26, buff, true, false, false);
  sprintf(buff, "AccTB: %2d", accelTB);
  if (stThrottle.sel == 1) { lcd.fillRoundRect(10, 40, 108, 14, 2, SH110X_WHITE); lcd_char(1, 16, 44, buff, false, false, false); }
  else                       lcd_char(1, 16, 44, buff, true, false, false);
}

//============================ SET DEFAULT ===============================
void handleSetDefault() {
  if (stSetDef.step == 0) {
    if (btnPressed(BTN_UP) || btnPressed(BTN_DOWN)) stSetDef.yes = !stSetDef.yes;
    if (btnPressed(BTN_OK))   { if (stSetDef.yes) stSetDef.step = 1; else popScreen(); return; }
    if (btnPressed(BTN_BACK)) { popScreen(); return; }
  } else if (stSetDef.step == 1) {
    for (byte p = 0; p < VAL_PLAN; p++) {
      resetOnePlan(p);
      for (byte i = 0; i < VAL_CHECKP; i++) { cpAct[p][i] = cpDelay[p][i] = cpTimerA[p][i] = cpReadIdx[p][i] = 0; }
    }
    plan = 0; normalSpeed = 80; stopIndex = 0; countCP = 0;
    saveHome(); saveAll();
    stSetDef.step = 2;
  } else {
    if (btnPressed(BTN_OK) || btnPressed(BTN_BACK)) { popScreen(); return; }
  }
}

void renderSetDefault() {
  if (stSetDef.step == 2) { lcd_char(1, 35, 28, "Selesai!", true, false, false); return; }
  lcd_char(1, 15, 12, "Set Default Robot?", true, false, false);
  if (!stSetDef.yes) { lcd.fillRoundRect(16, 32, 30, 14, 2, SH110X_WHITE); lcd_char(1, 22, 36, "No", false, false, false); lcd_char(1, 78, 36, "Yes", true, false, false); }
  else               { lcd.fillRoundRect(74, 32, 34, 14, 2, SH110X_WHITE); lcd_char(1, 22, 36, "No", true, false, false);  lcd_char(1, 80, 36, "Yes", false, false, false); }
}

//============================ RACE RESULT ===============================
void handleRaceResult() {
  if (btnPressed(BTN_OK) || btnPressed(BTN_BACK)) setScreen(SCR_HOME);
}

void renderRaceResult() {
  headUp(false, false);
  sprintf(buff, "Stop : %d", stResult.stopIdx);
  lcd_char(1, 5, 18, buff, true, false, false);
  sprintf(buff, "TIME : %.3f s", stResult.elapsed);
  lcd_char(1, 5, 30, buff, true, false, false);
  lcd_char(1, 5, 46, "Tekan OK / RUN", true, false, false);
}
