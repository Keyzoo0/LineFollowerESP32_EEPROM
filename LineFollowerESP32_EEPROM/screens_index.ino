// ===========================================================================
// Layar inti path-programming: Set Index (editor list datar), Add/Remove,
// Checkpoint. Editor lama 4-halaman diganti list datar yang konsisten &
// mudah dinavigasi (semua 14 parameter tetap ada).
// ===========================================================================

//=========================== helper plan ================================
void setIndexDefault(byte p, int i) {
  idx[p][i] = 0; logic[p][i] = 0; sensLogIdx[p][i] = 1;
  spdR[p][i] = 0; spdL[p][i] = 0; idelay[p][i] = 0;
  timerA[p][i] = 0; timerB[p][i] = 0; speedA[p][i] = 0; speedB[p][i] = 0;
  pidProfile[p][i] = 0; modeTIM[p][i] = 0; modeSens[p][i] = 0; usedSens[p][i] = 0;
}

void resetOnePlan(byte p) {
  for (int i = 0; i < VAL_INDEX; i++) {
    idx[p][i] = 0; logic[p][i] = 0; sensLogIdx[p][i] = 1;
    spdR[p][i] = 80; spdL[p][i] = 80; idelay[p][i] = 50;
    timerA[p][i] = 0; timerB[p][i] = 0; speedA[p][i] = 80; speedB[p][i] = 80;
    pidProfile[p][i] = 3; modeTIM[p][i] = 0; modeSens[p][i] = 0; usedSens[p][i] = 0;
  }
}

static void copyIndex(byte p, int dst, int src) {
  idx[p][dst] = idx[p][src]; logic[p][dst] = logic[p][src]; sensLogIdx[p][dst] = sensLogIdx[p][src];
  spdR[p][dst] = spdR[p][src]; spdL[p][dst] = spdL[p][src]; idelay[p][dst] = idelay[p][src];
  timerA[p][dst] = timerA[p][src]; timerB[p][dst] = timerB[p][src];
  speedA[p][dst] = speedA[p][src]; speedB[p][dst] = speedB[p][src];
  pidProfile[p][dst] = pidProfile[p][src]; modeTIM[p][dst] = modeTIM[p][src];
  modeSens[p][dst] = modeSens[p][src]; usedSens[p][dst] = usedSens[p][src];
}

static int clampi(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }

//============================== SET INDEX ===============================
#define IDX_ROWS 15
static const char* idxLabels[IDX_ROWS] = {
  "Index", "Trig SLog", "Trig Logic", "Action", "Speed L", "Speed R",
  "Act Delay", "PID Prof", "Speed A", "Timer A", "Mode TIM",
  "Speed B", "Timer B", "UsedSens", "FL Mode"
};

static String idxValue(int row) {
  int p = plan, i = stIdx.curIdx;
  switch (row) {
    case 0:  return String(i);
    case 1:  return String(sensLogIdx[p][i]);
    case 2:  return String(logika[logic[p][i]]);
    case 3:  return String(act[idx[p][i]]);
    case 4:  return String(spdL[p][i]);
    case 5:  return String(spdR[p][i]);
    case 6:  return String(idelay[p][i]);
    case 7:  return String(slctPID[pidProfile[p][i]]);
    case 8:  return String(speedA[p][i]);
    case 9:  return String(timerA[p][i]);
    case 10: return String(slctMode[modeTIM[p][i]]);
    case 11: return String(speedB[p][i]);
    case 12: return String(timerB[p][i]);
    case 13: return String(slctUsedSens[usedSens[p][i]]);
    case 14: return String(slctFLMODE[modeSens[p][i]]);
  }
  return "";
}

void handleSetIndex() {
  if (btnPressed(BTN_UP))   { if (--stIdx.row < 0) stIdx.row = IDX_ROWS - 1; }
  if (btnPressed(BTN_DOWN)) { if (++stIdx.row >= IDX_ROWS) stIdx.row = 0; }
  if (btnPressed(BTN_BACK)) { initEncoder(false); saveAll(); popScreen(); return; }

  int p = plan, i = stIdx.curIdx;
  bool up = btnRepeat(BTN_PLUS), dn = btnRepeat(BTN_MIN);

  switch (stIdx.row) {
    case 0:
      if (up) { if (++stIdx.curIdx >= VAL_INDEX) stIdx.curIdx = 0; }
      if (dn) { stIdx.curIdx = (stIdx.curIdx == 0) ? VAL_INDEX - 1 : stIdx.curIdx - 1; }
      if (btnPressed(BTN_OK)) { stAddRem.curIdx = stIdx.curIdx; pushScreen(SCR_ADDREMOVE); }
      break;
    case 1:  if (up) { if (++sensLogIdx[p][i] > 22) sensLogIdx[p][i] = 0; }
             if (dn) { sensLogIdx[p][i] = (sensLogIdx[p][i] == 0) ? 22 : sensLogIdx[p][i] - 1; } break;
    case 2:  if (up) { if (++logic[p][i] > 3) logic[p][i] = 0; }
             if (dn) { logic[p][i] = (logic[p][i] == 0) ? 3 : logic[p][i] - 1; } break;
    case 3:  if (up) { if (++idx[p][i] > 9) idx[p][i] = 0; }
             if (dn) { idx[p][i] = (idx[p][i] == 0) ? 9 : idx[p][i] - 1; } break;
    case 4:  if (up) spdL[p][i] = clampi(spdL[p][i] + 5, 0, 255);
             if (dn) spdL[p][i] = clampi(spdL[p][i] - 5, 0, 255); break;
    case 5:  if (up) spdR[p][i] = clampi(spdR[p][i] + 5, 0, 255);
             if (dn) spdR[p][i] = clampi(spdR[p][i] - 5, 0, 255); break;
    case 6:  if (up) idelay[p][i] = clampi(idelay[p][i] + 2, 0, 9999);
             if (dn) idelay[p][i] = clampi(idelay[p][i] - 2, 0, 9999); break;
    case 7:  if (up) { if (++pidProfile[p][i] > 6) pidProfile[p][i] = 0; }
             if (dn) { pidProfile[p][i] = (pidProfile[p][i] == 0) ? 6 : pidProfile[p][i] - 1; } break;
    case 8:  if (up) speedA[p][i] = clampi(speedA[p][i] + 5, 0, 255);
             if (dn) speedA[p][i] = clampi(speedA[p][i] - 5, 0, 255); break;
    case 9:  if (up) timerA[p][i] = clampi(timerA[p][i] + 1, 0, 9999);
             if (dn) timerA[p][i] = clampi(timerA[p][i] - 1, 0, 9999); break;
    case 10: if (up) { if (++modeTIM[p][i] > 2) modeTIM[p][i] = 0; }
             if (dn) { modeTIM[p][i] = (modeTIM[p][i] == 0) ? 2 : modeTIM[p][i] - 1; }
             if (modeTIM[p][i] == 1) { initEncoder(true); timerA[p][i] = measureLengthR(); }
             else if (modeTIM[p][i] == 2) { initEncoder(true); timerA[p][i] = measureLengthL(); }
             else initEncoder(false);
             break;
    case 11: if (up) speedB[p][i] = clampi(speedB[p][i] + 5, 0, 255);
             if (dn) speedB[p][i] = clampi(speedB[p][i] - 5, 0, 255); break;
    case 12: if (up) timerB[p][i] = clampi(timerB[p][i] + 1, 0, 9999);
             if (dn) timerB[p][i] = clampi(timerB[p][i] - 1, 0, 9999); break;
    case 13: if (up) { if (++usedSens[p][i] > 3) usedSens[p][i] = 0; }
             if (dn) { usedSens[p][i] = (usedSens[p][i] == 0) ? 3 : usedSens[p][i] - 1; } break;
    case 14: if (up) { if (++modeSens[p][i] > 2) modeSens[p][i] = 0; }
             if (dn) { modeSens[p][i] = (modeSens[p][i] == 0) ? 2 : modeSens[p][i] - 1; } break;
  }
}

void renderSetIndex() {
  headUpIdx(false, false, stIdx.curIdx);
  const int visible = 5;
  int top = clampi(stIdx.row - 2, 0, IDX_ROWS - visible);
  for (int r = 0; r < visible; r++) {
    int row = top + r;
    int y = 14 + r * 10;
    sprintf(buff, "%-9s: %s", idxLabels[row], idxValue(row).c_str());
    if (row == stIdx.row) {
      lcd.fillRoundRect(0, y - 1, 128, 10, 1, SH110X_WHITE);
      lcd_char(1, 3, y, buff, false, false, false);
    } else {
      lcd_char(1, 3, y, buff, true, false, false);
    }
  }
}

//============================== ADD / REMOVE ============================
void handleAddRemove() {
  int p = plan, i = stAddRem.curIdx;
  if (btnPressed(BTN_BACK)) { popScreen(); return; }
  if (btnPressed(BTN_PLUS)) {                 // sisip langkah baru di posisi i
    for (int c = VAL_INDEX - 1; c > i; c--) copyIndex(p, c, c - 1);
    setIndexDefault(p, i);
    saveAll(); popScreen(); return;
  }
  if (btnPressed(BTN_MIN)) {                   // hapus langkah di posisi i
    for (int c = i; c < VAL_INDEX - 1; c++) copyIndex(p, c, c + 1);
    setIndexDefault(p, VAL_INDEX - 1);
    saveAll(); popScreen(); return;
  }
}

void renderAddRemove() {
  sprintf(buff, "Plan-%d  Idx-%d", plan + 1, stAddRem.curIdx);
  lcd_char(1, 18, 10, buff, true, false, false);
  lcd.drawRoundRect(14, 28, 44, 16, 2, SH110X_WHITE);
  lcd_char(1, 20, 32, "+ Add", true, false, false);
  lcd.drawRoundRect(70, 28, 44, 16, 2, SH110X_WHITE);
  lcd_char(1, 76, 32, "- Del", true, false, false);
  lcd_char(1, 20, 52, "RUN = batal", true, false, false);
}

//============================== CHECKPOINT ==============================
void handleCheckpoint() {
  if (btnPressed(BTN_UP))   { if (--stCp.sel < 0) stCp.sel = 4; }
  if (btnPressed(BTN_DOWN)) { if (++stCp.sel > 4) stCp.sel = 0; }
  if (btnPressed(BTN_BACK)) { countCP = stCp.cp; saveHome(); saveAll(); popScreen(); return; }

  int p = plan, c = stCp.cp;
  bool up = btnRepeat(BTN_PLUS), dn = btnRepeat(BTN_MIN);
  switch (stCp.sel) {
    case 0: if (up) { if (++stCp.cp >= VAL_CHECKP) stCp.cp = 0; }
            if (dn) { stCp.cp = (stCp.cp == 0) ? VAL_CHECKP - 1 : stCp.cp - 1; } break;
    case 1: if (up) { if (++cpAct[p][c] > 3) cpAct[p][c] = 0; }
            if (dn) { cpAct[p][c] = (cpAct[p][c] == 0) ? 3 : cpAct[p][c] - 1; } break;
    case 2: if (up) cpDelay[p][c]++;  if (dn) cpDelay[p][c]--; break;
    case 3: if (up) cpTimerA[p][c]++; if (dn) cpTimerA[p][c]--; break;
    case 4: if (up) { if (++cpReadIdx[p][c] >= VAL_INDEX) cpReadIdx[p][c] = 0; }
            if (dn) { cpReadIdx[p][c] = (cpReadIdx[p][c] == 0) ? VAL_INDEX - 1 : cpReadIdx[p][c] - 1; } break;
  }
}

void renderCheckpoint() {
  int p = plan, c = stCp.cp;
  sprintf(buff, "PLAN-%d  CP-%d", p + 1, c);
  lcd_char(1, 6, 2, buff, true, false, false);
  lcd.drawLine(0, 12, 128, 12, SH110X_WHITE);
  String rows[5] = {
    "Pilih CP : " + String(c),
    "Action   : " + String(actCheckpoint[cpAct[p][c]]),
    "D Act    : " + String(cpDelay[p][c]) + " ms",
    "Timer A  : " + String(cpTimerA[p][c]) + " ms",
    "Read Idx : " + String(cpReadIdx[p][c])
  };
  for (int i = 0; i < 5; i++) {
    int y = 16 + i * 9;
    if (i == stCp.sel) { lcd.fillRoundRect(0, y - 1, 128, 9, 1, SH110X_WHITE); lcd_char(1, 4, y, rows[i], false, false, false); }
    else                 lcd_char(1, 4, y, rows[i], true, false, false);
  }
}
