// ===========================================================================
// STORAGE — EEPROM (konfigurasi) + SPI Flash (plan & checkpoint).
// Plan/checkpoint diserialisasi lewat blob TRANSIEN (bukan struct global ganda),
// jadi tidak ada duplikasi RAM 15KB & tidak ada bug sinkronisasi 2 arah.
//   Layout flash : plan[0..8] @ p*sizeof(PlanBlob), lalu checkpoint[0..8].
//   Total ~15.6 KB  ->  cukup di eraseBlock32K(0).
// ===========================================================================

struct PlanBlob {
  uint8_t idx[VAL_INDEX];
  uint8_t logic[VAL_INDEX];
  uint8_t sensLogIdx[VAL_INDEX];
  uint8_t spdR[VAL_INDEX];
  uint8_t spdL[VAL_INDEX];
  uint8_t idelayH[VAL_INDEX], idelayL[VAL_INDEX];
  uint8_t timerAH[VAL_INDEX], timerAL[VAL_INDEX];
  uint8_t timerBH[VAL_INDEX], timerBL[VAL_INDEX];
  uint8_t speedA[VAL_INDEX];
  uint8_t speedB[VAL_INDEX];
  uint8_t pidProfile[VAL_INDEX];
  uint8_t modeTIM[VAL_INDEX];
  uint8_t modeSens[VAL_INDEX];
  uint8_t usedSens[VAL_INDEX];
};

struct CPBlob {
  uint8_t act[VAL_CHECKP];
  uint8_t delayv[VAL_CHECKP];
  uint8_t timerA[VAL_CHECKP];
  uint8_t readIdx[VAL_CHECKP];
};

static const uint32_t CP_BASE = (uint32_t)VAL_PLAN * sizeof(PlanBlob);

//=============================== PLAN ====================================
void savePlans() {
  static PlanBlob blob;
  for (uint8_t p = 0; p < VAL_PLAN; p++) {
    for (uint8_t i = 0; i < VAL_INDEX; i++) {
      blob.idx[i]        = idx[p][i];
      blob.logic[i]      = logic[p][i];
      blob.sensLogIdx[i] = sensLogIdx[p][i];
      blob.spdR[i]       = spdR[p][i];
      blob.spdL[i]       = spdL[p][i];
      blob.idelayH[i]    = idelay[p][i] >> 8;   blob.idelayL[i] = idelay[p][i] & 0xFF;
      blob.timerAH[i]    = timerA[p][i] >> 8;   blob.timerAL[i] = timerA[p][i] & 0xFF;
      blob.timerBH[i]    = timerB[p][i] >> 8;   blob.timerBL[i] = timerB[p][i] & 0xFF;
      blob.speedA[i]     = speedA[p][i];
      blob.speedB[i]     = speedB[p][i];
      blob.pidProfile[i] = pidProfile[p][i];
      blob.modeTIM[i]    = modeTIM[p][i];
      blob.modeSens[i]   = modeSens[p][i];
      blob.usedSens[i]   = usedSens[p][i];
    }
    memory.writeByteArray((uint32_t)p * sizeof(PlanBlob), (uint8_t*)&blob, sizeof(PlanBlob));
  }
}

void loadPlans() {
  static PlanBlob blob;
  for (uint8_t p = 0; p < VAL_PLAN; p++) {
    memory.readByteArray((uint32_t)p * sizeof(PlanBlob), (uint8_t*)&blob, sizeof(PlanBlob));
    for (uint8_t i = 0; i < VAL_INDEX; i++) {
      idx[p][i]        = blob.idx[i];
      logic[p][i]      = blob.logic[i];
      sensLogIdx[p][i] = blob.sensLogIdx[i];
      spdR[p][i]       = blob.spdR[i];
      spdL[p][i]       = blob.spdL[i];
      idelay[p][i]     = (blob.idelayH[i] << 8) | blob.idelayL[i];
      timerA[p][i]     = (blob.timerAH[i] << 8) | blob.timerAL[i];
      timerB[p][i]     = (blob.timerBH[i] << 8) | blob.timerBL[i];
      speedA[p][i]     = blob.speedA[i];
      speedB[p][i]     = blob.speedB[i];
      pidProfile[p][i] = blob.pidProfile[i];
      modeTIM[p][i]    = blob.modeTIM[i];
      modeSens[p][i]   = blob.modeSens[i];
      usedSens[p][i]   = blob.usedSens[i];
    }
  }
}

//============================ CHECKPOINT =================================
void saveCheckpoints() {
  static CPBlob blob;
  for (uint8_t p = 0; p < VAL_PLAN; p++) {
    for (uint8_t i = 0; i < VAL_CHECKP; i++) {
      blob.act[i]     = cpAct[p][i];
      blob.delayv[i]  = cpDelay[p][i];
      blob.timerA[i]  = cpTimerA[p][i];
      blob.readIdx[i] = cpReadIdx[p][i];
    }
    memory.writeByteArray(CP_BASE + (uint32_t)p * sizeof(CPBlob), (uint8_t*)&blob, sizeof(CPBlob));
  }
}

void loadCheckpoints() {
  static CPBlob blob;
  for (uint8_t p = 0; p < VAL_PLAN; p++) {
    memory.readByteArray(CP_BASE + (uint32_t)p * sizeof(CPBlob), (uint8_t*)&blob, sizeof(CPBlob));
    for (uint8_t i = 0; i < VAL_CHECKP; i++) {
      cpAct[p][i]     = blob.act[i];
      cpDelay[p][i]   = blob.delayv[i];
      cpTimerA[p][i]  = blob.timerA[i];
      cpReadIdx[p][i] = blob.readIdx[i];
    }
  }
}

void saveAll() {
  SLED(1);
  memory.eraseBlock32K(0);
  savePlans();
  saveCheckpoints();
  SLED(0);
}

//=============================== EEPROM ==================================
void saveHome() {
  EEPROM.write(addrPlan, plan);
  EEPROM.write(addrNS,   normalSpeed);
  EEPROM.write(addrSI,   stopIndex);
  EEPROM.write(addrCCP,  countCP);
  EEPROM.commit();
}
void readHome() {
  plan        = EEPROM.read(addrPlan);
  normalSpeed = EEPROM.read(addrNS);
  stopIndex   = EEPROM.read(addrSI);
  countCP     = EEPROM.read(addrCCP);
}

void savePID() {
  for (int i = 0; i < 7; i++) {
    EEPROM.write(addrKp + i, (uint8_t)(Kp[i] * 10.0));
    EEPROM.write(addrKi + i, (uint8_t)(Ki[i] * 100.0));
    EEPROM.write(addrKd + i, (uint8_t)(Kd[i]));
  }
  EEPROM.commit();
}
void readPID() {
  for (int i = 0; i < 7; i++) {
    Kp[i] = EEPROM.read(addrKp + i) * 0.1;
    Ki[i] = EEPROM.read(addrKi + i) * 0.01;
    Kd[i] = EEPROM.read(addrKd + i);
  }
}

void saveCalib() {
  for (uint8_t i = 0; i < MAXSENSOR; i++) {
    EEPROM.write(addrCalibH + i, CalAdc[i] >> 8);
    EEPROM.write(addrCalibL + i, CalAdc[i] & 0xFF);
  }
  EEPROM.commit();
}
void readCalib() {
  for (uint8_t i = 0; i < MAXSENSOR; i++)
    CalAdc[i] = (EEPROM.read(addrCalibH + i) << 8) | EEPROM.read(addrCalibL + i);
}

void saveMaxMin() {
  for (uint8_t i = 0; i < MAXSENSOR; i++) {
    EEPROM.write(addrsetMaxSensH + i, setMaxVal[i] >> 8);
    EEPROM.write(addrsetMaxSensL + i, setMaxVal[i] & 0xFF);
    EEPROM.write(addrsetMinSensH + i, setMinVal[i] >> 8);
    EEPROM.write(addrsetMinSensL + i, setMinVal[i] & 0xFF);
  }
  EEPROM.commit();
}
void readMaxMin() {
  for (uint8_t i = 0; i < MAXSENSOR; i++) {
    setMaxVal[i] = (EEPROM.read(addrsetMaxSensH + i) << 8) | EEPROM.read(addrsetMaxSensL + i);
    setMinVal[i] = (EEPROM.read(addrsetMinSensH + i) << 8) | EEPROM.read(addrsetMinSensL + i);
  }
}

void saveSensSens() { EEPROM.write(addrSensSev, sensorSensivity); EEPROM.commit(); }
void readSensSens() { sensorSensivity = EEPROM.read(addrSensSev); }

void saveAccel() { EEPROM.write(addrAccelTA, accelTA); EEPROM.write(addrAccelTB, accelTB); EEPROM.commit(); }
void readAccel() {
  accelTA = EEPROM.read(addrAccelTA); if (accelTA == 0 || accelTA > 25) accelTA = 2;
  accelTB = EEPROM.read(addrAccelTB); if (accelTB == 0 || accelTB > 25) accelTB = 2;
}

//=============================== setup ===================================
void setupStorage() {
  memory.begin();
  EEPROM.begin(EEPROM_SIZE);
  readHome();
  readSensSens();
  readMaxMin();
  readCalib();
  readPID();
  readAccel();
  loadPlans();
  loadCheckpoints();
}
