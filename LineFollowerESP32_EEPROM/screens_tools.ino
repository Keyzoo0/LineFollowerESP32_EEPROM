// ===========================================================================
// Layar tools: Calib (auto/manual), Tune PID, Test Motor, Copy/Mirror, Reset.
// ===========================================================================

//============================ CALIB (pilih) =============================
void handleCalib() {
  if (btnPressed(BTN_UP) || btnPressed(BTN_DOWN)) stCalib.sel = !stCalib.sel;
  if (btnPressed(BTN_BACK)) { saveAll(); popScreen(); return; }
  if (btnPressed(BTN_OK)) pushScreen(stCalib.sel == 0 ? SCR_CALIB_AUTO : SCR_CALIB_MANUAL);
}
void renderCalib() {
  lcd_char(1, 15, 2, "Calib Sensor", true, false, false);
  lcd.drawLine(0, 12, 128, 12, SH110X_WHITE);
  displaySensor(readSensor());
  const char* it[2] = { "Auto", "Manual" };
  for (int i = 0; i < 2; i++) {
    int y = 38 + i * 14;
    if (i == stCalib.sel) { lcd.fillRoundRect(30, y - 1, 68, 12, 2, SH110X_WHITE); lcd_char(1, 50, y + 1, it[i], false, false, false); }
    else                    lcd_char(1, 50, y + 1, it[i], true, false, false);
  }
}

//============================== CALIB AUTO ==============================
void handleCalibAuto() {
  if (btnPressed(BTN_BACK)) { saveAll(); popScreen(); return; }

  if (stCalAuto.step == 0) {
    if (btnRepeat(BTN_PLUS)) { if (++sensorSensivity > 100) sensorSensivity = 0; saveSensSens(); }
    if (btnRepeat(BTN_MIN))  { sensorSensivity = (sensorSensivity == 0) ? 100 : sensorSensivity - 1; saveSensSens(); }
    if (btnPressed(BTN_OK)) {
      for (int i = 0; i < MAXSENSOR; i++) { setMinVal[i] = 1023; setMaxVal[i] = 0; }
      stCalAuto.step = 1;
    }
  } else if (stCalAuto.step == 1) {
    readSensor();                                   // isi adcVal[]
    for (int i = 0; i < MAXSENSOR; i++) {
      if (adcVal[i] > setMaxVal[i]) setMaxVal[i] = adcVal[i];
      if (adcVal[i] < setMinVal[i]) setMinVal[i] = adcVal[i];
    }
    if (btnPressed(BTN_OK)) {
      for (int i = 0; i < MAXSENSOR; i++)
        CalAdc[i] = (uint16_t)((setMaxVal[i] - setMinVal[i]) * ((100.0 - sensorSensivity) / 100.0) + setMinVal[i]);
      saveCalib(); saveMaxMin();
      stCalAuto.step = 2;
    }
  } else {
    if (btnPressed(BTN_OK)) { saveAll(); popScreen(); return; }
  }
}
void renderCalibAuto() {
  lcd_char(1, 30, 2, "Auto Calib", true, false, false);
  lcd.drawLine(0, 12, 128, 12, SH110X_WHITE);
  if (stCalAuto.step == 0) {
    sprintf(buff, "Sensivity : %d", sensorSensivity);
    lcd_char(1, 8, 24, buff, true, false, false);
    lcd_char(1, 8, 40, "+/-: atur   OK: scan", true, false, false);
  } else if (stCalAuto.step == 1) {
    displaySensor(readSensor());
    lcd_char(1, 25, 40, "Scanning...", true, false, false);
    lcd_char(1, 18, 52, "Geser di garis, OK", true, false, false);
  } else {
    lcd_char(1, 12, 28, "Kalibrasi sukses!", true, false, false);
    lcd_char(1, 35, 44, "OK = keluar", true, false, false);
  }
}

//============================= CALIB MANUAL =============================
void handleCalibManual() {
  if (btnPressed(BTN_BACK)) { saveCalib(); saveMaxMin(); saveAll(); popScreen(); return; }
  if (btnPressed(BTN_UP))   { if (++stCalMan.menu > 13) stCalMan.menu = 0; }
  if (btnPressed(BTN_DOWN)) { stCalMan.menu = (stCalMan.menu == 0) ? 13 : stCalMan.menu - 1; }
  if (btnPressed(BTN_OK))   { if (++stCalMan.sel > 2) stCalMan.sel = 0; }

  int s = stCalMan.menu;
  bool up = btnRepeat(BTN_PLUS), dn = btnRepeat(BTN_MIN);
  if (stCalMan.sel == 0)      { if (up) setMaxVal[s] = clampi(setMaxVal[s] + 1, 0, 1023); if (dn) setMaxVal[s] = clampi(setMaxVal[s] - 1, 0, 1023); }
  else if (stCalMan.sel == 1) { if (up) setMinVal[s] = clampi(setMinVal[s] + 1, 0, 1023); if (dn) setMinVal[s] = clampi(setMinVal[s] - 1, 0, 1023); }
  else                        { if (up) CalAdc[s]    = clampi(CalAdc[s] + 1, 0, 1023);    if (dn) CalAdc[s]    = clampi(CalAdc[s] - 1, 0, 1023); }
}
void renderCalibManual() {
  readSensor();
  int s = stCalMan.menu;
  sprintf(buff, "Manual  Sensor %02d", s + 1);
  lcd_char(1, 8, 2, buff, true, false, false);
  lcd.drawLine(0, 12, 128, 12, SH110X_WHITE);
  String rows[3] = {
    "MAX : " + String(setMaxVal[s]),
    "MIN : " + String(setMinVal[s]),
    "SET : " + String(CalAdc[s])
  };
  for (int i = 0; i < 3; i++) {
    int y = 18 + i * 11;
    if (i == stCalMan.sel) { lcd.fillRoundRect(0, y - 1, 80, 10, 1, SH110X_WHITE); lcd_char(1, 4, y, rows[i], false, false, false); }
    else                     lcd_char(1, 4, y, rows[i], true, false, false);
  }
  lcd_char(1, 86, 18, "READ", true, false, false);
  lcd_char(1, 86, 30, String(adcVal[s]), true, false, false);
  lcd_char(1, 4, 54, "UP/DN sensor  OK field", true, false, false);
}

//=============================== TUNE PID ===============================
static void runPidTest(byte mode, byte preset) {
  if (readBattery() < minBat) return;
  unsigned long lastF = 0;
  while (1) {
    inputUpdate();
    int ds = readSensor();
    program(ds, mode, normalSpeed, preset, 0);
    if (btnPressed(BTN_BACK) || btnPressed(BTN_OK)) { stopMotor(); break; }
    if (millis() - lastF >= FRAME_MS) {
      lastF = millis();
      lcd.clearDisplay();
      lcd_char(1, 20, 2, "Coba PID...", true, false, false);
      lcd.drawLine(0, 12, 128, 12, SH110X_WHITE);
      displaySensor(ds);
      lcd_char(1, 10, 52, "RUN/OK = stop", true, false, false);
      lcd.display();
    }
  }
}

void handleTunePid() {
  if (btnPressed(BTN_BACK)) { savePID(); popScreen(); return; }
  if (btnPressed(BTN_UP))   { if (--stTune.sel < 1) stTune.sel = 6; }
  if (btnPressed(BTN_DOWN)) { if (++stTune.sel > 6) stTune.sel = 1; }

  bool up = btnRepeat(BTN_PLUS), dn = btnRepeat(BTN_MIN);
  switch (stTune.sel) {
    case 1: if (btnPressed(BTN_PLUS)) { if (++stTune.preset > 6) stTune.preset = 0; }
            if (btnPressed(BTN_MIN))  { stTune.preset = (stTune.preset == 0) ? 6 : stTune.preset - 1; } break;
    case 2: if (up) { Kp[stTune.preset] += 0.1; savePID(); } if (dn) { Kp[stTune.preset] -= 0.1; savePID(); } break;
    case 3: if (up) { Kd[stTune.preset] += 1.0; savePID(); } if (dn) { Kd[stTune.preset] -= 1.0; savePID(); } break;
    case 4: if (up) { Ki[stTune.preset] += 0.01; savePID(); } if (dn) { Ki[stTune.preset] -= 0.01; savePID(); } break;
    case 5: if (btnPressed(BTN_PLUS)) { if (++stTune.flmode > 2) stTune.flmode = 0; }
            if (btnPressed(BTN_MIN))  { stTune.flmode = (stTune.flmode == 0) ? 2 : stTune.flmode - 1; } break;
    case 6: if (btnPressed(BTN_OK)) { runPidTest(stTune.flmode, stTune.preset); } break;
  }
  if (Kp[stTune.preset] < 0) Kp[stTune.preset] = 0;
  if (Kd[stTune.preset] < 0) Kd[stTune.preset] = 0;
  if (Ki[stTune.preset] < 0) Ki[stTune.preset] = 0;
}
void renderTunePid() {
  headUp(false, false);
  sprintf(buff, "Preset: %s", slctPID[stTune.preset]);
  lcd_char(1, 8, 15, buff, true, false, false);
  if (stTune.sel == 1) lcd.drawRect(2, 13, 124, 11, SH110X_WHITE);

  sprintf(buff, "Kp:%.1f", Kp[stTune.preset]);
  lcd_char(1, 6, 28, buff, true, false, false);   if (stTune.sel == 2) lcd.drawRect(2, 26, 58, 11, SH110X_WHITE);
  sprintf(buff, "Kd:%.0f", Kd[stTune.preset]);
  lcd_char(1, 68, 28, buff, true, false, false);  if (stTune.sel == 3) lcd.drawRect(64, 26, 60, 11, SH110X_WHITE);
  sprintf(buff, "Ki:%.3f", Ki[stTune.preset]);
  lcd_char(1, 6, 40, buff, true, false, false);   if (stTune.sel == 4) lcd.drawRect(2, 38, 70, 11, SH110X_WHITE);
  sprintf(buff, "FL:%s", slctFLMODE[stTune.flmode]);
  lcd_char(1, 80, 40, buff, true, false, false);  if (stTune.sel == 5) lcd.drawRect(76, 38, 48, 11, SH110X_WHITE);

  lcd_char(1, 35, 53, "Coba PID", stTune.sel != 6, false, false);
  if (stTune.sel == 6) { lcd.fillRoundRect(30, 51, 64, 11, 2, SH110X_WHITE); lcd_char(1, 35, 53, "Coba PID", false, false, false); }
}

//============================== TEST MOTOR =============================
void handleTestMotor() {
  if (btnPressed(BTN_BACK)) { stopMotor(); initEncoder(false); popScreen(); return; }
  if (btnPressed(BTN_OK))   stTest.col = !stTest.col;           // pilih motor kiri/kanan
  if (btnPressed(BTN_UP) || btnPressed(BTN_DOWN)) stTest.row = !stTest.row; // dir / speed

  bool up = btnRepeat(BTN_PLUS), dn = btnRepeat(BTN_MIN);
  if (stTest.col == 0) {            // motor kiri
    if (stTest.row == 0) { if (btnPressed(BTN_PLUS)) { if (++stTest.dirL > 2) stTest.dirL = 0; } if (btnPressed(BTN_MIN)) { stTest.dirL = (stTest.dirL == 0) ? 2 : stTest.dirL - 1; } }
    else                 { if (up) stTest.spL = clampi(stTest.spL + 5, 0, 255); if (dn) stTest.spL = clampi(stTest.spL - 5, 0, 255); }
  } else {                          // motor kanan
    if (stTest.row == 0) { if (btnPressed(BTN_PLUS)) { if (++stTest.dirR > 2) stTest.dirR = 0; } if (btnPressed(BTN_MIN)) { stTest.dirR = (stTest.dirR == 0) ? 2 : stTest.dirR - 1; } }
    else                 { if (up) stTest.spR = clampi(stTest.spR + 5, 0, 255); if (dn) stTest.spR = clampi(stTest.spR - 5, 0, 255); }
  }

  int outL = (stTest.dirL == 2) ? 0 : (stTest.dirL == 0 ? stTest.spL : -stTest.spL);
  int outR = (stTest.dirR == 2) ? 0 : (stTest.dirR == 0 ? stTest.spR : -stTest.spR);
  pwmMotor(outL, outR);
}
void renderTestMotor() {
  const char* dir[3] = { "F", "B", "S" };
  lcd_char(1, 30, 2, "Test Motor", true, false, false);
  lcd.drawLine(0, 12, 128, 12, SH110X_WHITE);

  if (stTest.col == 0) lcd.fillRoundRect(0, 14, 62, 11, 2, SH110X_WHITE);
  else                 lcd.drawRoundRect(0, 14, 62, 11, 2, SH110X_WHITE);
  lcd_char(1, 6, 16, "MTR Kiri", stTest.col != 0, false, false);
  if (stTest.col == 1) lcd.fillRoundRect(66, 14, 62, 11, 2, SH110X_WHITE);
  else                 lcd.drawRoundRect(66, 14, 62, 11, 2, SH110X_WHITE);
  lcd_char(1, 72, 16, "MTR Kanan", stTest.col != 1, false, false);

  sprintf(buff, "Dir:%s", dir[stTest.dirL]); lcd_char(1, 4, 30, buff, true, false, false);
  sprintf(buff, "Spd:%d", stTest.spL);       lcd_char(1, 4, 42, buff, true, false, false);
  sprintf(buff, "Enc:%d", countEnc_A);       lcd_char(1, 4, 54, buff, true, false, false);
  sprintf(buff, "Dir:%s", dir[stTest.dirR]); lcd_char(1, 70, 30, buff, true, false, false);
  sprintf(buff, "Spd:%d", stTest.spR);       lcd_char(1, 70, 42, buff, true, false, false);
  sprintf(buff, "Enc:%d", countEnc_B);       lcd_char(1, 70, 54, buff, true, false, false);

  if (stTest.col == 0) lcd_char(1, 48, stTest.row == 0 ? 30 : 42, "<", true, false, false);
  else                 lcd_char(1, 114, stTest.row == 0 ? 30 : 42, "<", true, false, false);
}

//============================== COPY / MIRROR ==========================
static byte mirrorSlog(byte v) {
  switch (v) {
    case 2: return 3;  case 3: return 2;  case 4: return 5;  case 5: return 4;
    case 6: return 7;  case 7: return 6;  case 8: return 9;  case 9: return 8;
    case 10: return 11; case 11: return 10; case 12: return 13; case 13: return 12;
    case 16: return 17; case 17: return 16; case 18: return 19; case 19: return 18;
  }
  return v;
}
static void doCopyMirror() {
  byte a = stCM.x1, b = stCM.x2;
  for (int i = 0; i < VAL_INDEX; i++) {
    // copy semua field a -> b
    logic[b][i] = logic[a][i]; spdR[b][i] = spdR[a][i]; spdL[b][i] = spdL[a][i];
    idelay[b][i] = idelay[a][i]; timerA[b][i] = timerA[a][i]; timerB[b][i] = timerB[a][i];
    speedA[b][i] = speedA[a][i]; speedB[b][i] = speedB[a][i]; pidProfile[b][i] = pidProfile[a][i];
    modeTIM[b][i] = modeTIM[a][i]; usedSens[b][i] = usedSens[a][i];
    if (!stCM.mirror) {
      idx[b][i] = idx[a][i]; sensLogIdx[b][i] = sensLogIdx[a][i]; modeSens[b][i] = modeSens[a][i];
    } else {
      byte v = idx[a][i];
      if (v == 2) v = 3; else if (v == 3) v = 2; else if (v == 7) v = 8; else if (v == 8) v = 7;
      idx[b][i] = v;
      sensLogIdx[b][i] = mirrorSlog(sensLogIdx[a][i]);
      modeSens[b][i] = (modeSens[a][i] == 1) ? 2 : (modeSens[a][i] == 2 ? 1 : modeSens[a][i]);
    }
  }
  saveAll();
}
void handleCopyMirror() {
  if (btnPressed(BTN_BACK)) { popScreen(); return; }
  if (btnPressed(BTN_UP))   { if (++stCM.step > 3) stCM.step = 1; }
  if (btnPressed(BTN_DOWN)) { if (--stCM.step < 1) stCM.step = 3; }
  if (stCM.step == 1) { if (btnPressed(BTN_PLUS) || btnPressed(BTN_MIN)) stCM.mirror = !stCM.mirror; }
  if (stCM.step == 2) { if (btnPressed(BTN_PLUS)) { if (++stCM.x1 >= VAL_PLAN) stCM.x1 = 0; } if (btnPressed(BTN_MIN)) { stCM.x1 = (stCM.x1 == 0) ? VAL_PLAN - 1 : stCM.x1 - 1; } }
  if (stCM.step == 3) { if (btnPressed(BTN_PLUS)) { if (++stCM.x2 >= VAL_PLAN) stCM.x2 = 0; } if (btnPressed(BTN_MIN)) { stCM.x2 = (stCM.x2 == 0) ? VAL_PLAN - 1 : stCM.x2 - 1; } }
  if (btnPressed(BTN_OK)) { if (stCM.x1 != stCM.x2) { doCopyMirror(); popScreen(); return; } }
}
void renderCopyMirror() {
  lcd_char(1, 12, 2, "Copy / Mirror Plan", true, false, false);
  lcd.drawLine(0, 12, 128, 12, SH110X_WHITE);
  sprintf(buff, "Mode : %s", stCM.mirror ? "Mirror" : "Copy");
  lcd_char(1, 6, 18, buff, stCM.step != 1, false, false); if (stCM.step == 1) { lcd.fillRoundRect(0, 17, 120, 10, 1, SH110X_WHITE); lcd_char(1, 6, 18, buff, false, false, false); }
  sprintf(buff, "Dari : P%d", stCM.x1 + 1);
  lcd_char(1, 6, 30, buff, stCM.step != 2, false, false); if (stCM.step == 2) { lcd.fillRoundRect(0, 29, 120, 10, 1, SH110X_WHITE); lcd_char(1, 6, 30, buff, false, false, false); }
  sprintf(buff, "Ke   : P%d", stCM.x2 + 1);
  lcd_char(1, 6, 42, buff, stCM.step != 3, false, false); if (stCM.step == 3) { lcd.fillRoundRect(0, 41, 120, 10, 1, SH110X_WHITE); lcd_char(1, 6, 42, buff, false, false, false); }
  lcd_char(1, 6, 54, (stCM.x1 == stCM.x2) ? "Plan sama! pilih beda" : "OK = jalankan", true, false, false);
}

//============================== RESET PLAN =============================
void handleResetPlan() {
  if (stReset.step == 0) {
    if (btnPressed(BTN_UP) || btnPressed(BTN_DOWN)) stReset.yes = !stReset.yes;
    if (btnPressed(BTN_OK))   { if (stReset.yes) stReset.step = 1; else popScreen(); return; }
    if (btnPressed(BTN_BACK)) { popScreen(); return; }
  } else if (stReset.step == 1) {
    resetOnePlan(stReset.target);
    saveAll();
    stReset.step = 2;
  } else {
    if (btnPressed(BTN_OK) || btnPressed(BTN_BACK)) { popScreen(); return; }
  }
}
void renderResetPlan() {
  if (stReset.step == 2) { sprintf(buff, "P%d Terhapus!", stReset.target + 1); lcd_char(1, 25, 28, buff, true, false, false); return; }
  sprintf(buff, "Hapus Plan P%d ?", stReset.target + 1);
  lcd_char(1, 15, 12, buff, true, false, false);
  if (!stReset.yes) { lcd.fillRoundRect(16, 32, 30, 14, 2, SH110X_WHITE); lcd_char(1, 22, 36, "No", false, false, false); lcd_char(1, 78, 36, "Yes", true, false, false); }
  else              { lcd.fillRoundRect(74, 32, 34, 14, 2, SH110X_WHITE); lcd_char(1, 22, 36, "No", true, false, false);  lcd_char(1, 80, 36, "Yes", false, false, false); }
}
