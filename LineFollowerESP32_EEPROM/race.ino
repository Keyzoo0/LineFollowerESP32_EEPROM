// ===========================================================================
// RACE — loop balapan real-time. Tetap loop ketat (deterministik untuk kontrol)
// TAPI: input dibaca non-blocking tiap iterasi (abort responsif) & semua
// timing pakai millis() (tanpa delay()). Ramp memakai accelTA/accelTB (Settings).
// ===========================================================================

static bool raceAbort() { return btnPressed(BTN_OK) || btnPressed(BTN_BACK); }

// Jalankan motor (l,r) selama ms, sambil tetap memantau tombol abort.
static void actRun(int l, int r, long ms) {
  long t0 = millis();
  while (millis() - t0 < ms) {
    inputUpdate();
    if (raceAbort()) { stopMotor(); return; }
    pwmMotor(l, r);
  }
}

// Aksi diskrit per langkah (FORWARD/LEFT/.../FAN). PICK/DROP/FAN no-op (HW belum ada).
static void execAction(int s) {
  int  p = plan;
  byte a = idx[p][s];
  long d = idelay[p][s];
  switch (a) {
    case 0: actRun(0, 0, d * 15); break;                       // STOP
    case 1: actRun(spdL[p][s],  spdR[p][s],  d * 10); break;   // FORWARD
    case 2: actRun(-spdL[p][s], spdR[p][s],  d * 4);  break;   // LEFT
    case 3: actRun(spdL[p][s],  -spdR[p][s], d * 4);  break;   // RIGHT
    case 4: actRun(-spdL[p][s], -spdR[p][s], d * 10); break;   // BACKWARD
    case 5: break;                                             // PICK (no-op)
    case 6: break;                                             // DROP (no-op)
    case 7: actRun(-200, 200, d * 4); break;                   // TLEFT
    case 8: actRun(200, -200, d * 4); break;                   // TRIGHT
    case 9: actRun(0, 0, d * 15); break;                       // FAN (no-op stop)
  }
}

void runRace() {
  int  start;
  int  stopCount = stopIndex;
  bool protec    = false;

  if (countCP > 0) { start = cpReadIdx[plan][countCP]; protec = true; }
  else             { start = 0; }
  if (stopCount == 0) stopCount = VAL_INDEX - 1;

  initEncoder(false);
  sumError = 0; lastError = 0;
  sw_millis.reset();
  sw_millis.start();

  lcd.clearDisplay();
  lcd.drawBitmap(0, -5, Logo_EEPROM, 128, 64, SH110X_WHITE);
  lcd.display();

  // --- segmen pemanasan dari checkpoint ---
  if (protec) {
    long TA = cpDelay[plan][countCP];
    long t0 = millis();
    int target = normalSpeed;
    int ramp = target / 4;
    while ((millis() - t0) < (TA * 1)) {
      inputUpdate();
      if (raceAbort()) goto finish;
      if (ramp < target) { ramp += accelTA; if (ramp > target) ramp = target; }
      program(readSensor(), modeSens[plan][start], ramp, pidProfile[plan][start], usedSens[plan][start]);
    }
    if (start == stopCount) goto finish;
    start = cpReadIdx[plan][countCP] + 1;
  }

  // --- loop utama ---
  while (1) {
    inputUpdate();
    if (raceAbort()) break;

    int ds = readSensor();
    unsigned int setSensor = sensLog[sensLogIdx[plan][start]];
    byte lg = logic[plan][start];
    bool do_action = false;

    if (lg == 0)      { if (ds & setSensor) do_action = true;
                        else program(ds, modeSens[plan][start], normalSpeed, pidProfile[plan][start], usedSens[plan][start]); }
    else if (lg == 1) { if ((ds & setSensor) == setSensor) do_action = true;
                        else program(ds, modeSens[plan][start], normalSpeed, pidProfile[plan][start], usedSens[plan][start]); }
    else if (lg == 2) { do_action = true; }            // TIM
    // lg == 3 (XOR) belum dipakai

    if (do_action) {
      execAction(start);

      // fase A
      long TA = timerA[plan][start];
      long tA = millis();
      int  targetA = speedA[plan][start];
      int  rampA = targetA / 4;
      while (1) {
        inputUpdate();
        if (raceAbort()) goto finish;
        if (rampA < targetA) { rampA += accelTA; if (rampA > targetA) rampA = targetA; }
        program(readSensor(), modeSens[plan][start], (rampA < 50 ? 50 : rampA),
                pidProfile[plan][start], usedSens[plan][start]);
        if (TA > 0) { if ((millis() - tA) > (unsigned long)TA * 15) break; } else break;
      }

      // fase B
      long TB = timerB[plan][start];
      long tB = millis();
      int  targetB = speedB[plan][start];
      int  rampB = (TA == 0) ? targetB / 4 : speedA[plan][start];
      while (1) {
        inputUpdate();
        if (raceAbort()) goto finish;
        int spd;
        if (TA == 0)                          { rampB += accelTB; if (rampB > targetB) rampB = targetB; spd = (rampB < 50 ? 50 : rampB); }
        else if (targetB > speedA[plan][start]) { rampB += accelTB; if (rampB > targetB) rampB = targetB; spd = rampB; }
        else if (targetB < speedA[plan][start]) { rampB -= accelTB; if (rampB < targetB) rampB = targetB; spd = rampB; }
        else                                    { spd = targetB; }
        program(readSensor(), modeSens[plan][start], spd, pidProfile[plan][start], usedSens[plan][start]);
        if (TB > 0) { if ((millis() - tB) > (unsigned long)TB * 15) break; } else break;
      }

      if (start >= stopCount) break;
      start++;
    }
  }

finish:
  sw_millis.stop();
  stopMotor();
  stResult.stopIdx = start;
  stResult.elapsed = sw_millis.elapsed() * 0.001;
  setScreen(SCR_RACE_RESULT);
}
