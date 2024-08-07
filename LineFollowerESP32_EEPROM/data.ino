// #include "data.h"
 void saveAll() {
  // SLED(1);
  eraseSec(0);
  saveCalib();
  saveHome();
  saveSensorSensivity();
  savePID();
  save_PID();
  saveMaxMinSens();
  // SLED(0);
}

void saveIdxAll(){
  // SLED(1);
  eraseSec(4096);
  eraseSec(8192);
  saveIdx();
  // SLED(0);
}
