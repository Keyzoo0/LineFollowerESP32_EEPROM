#ifndef DATA_H
#define DATA_H

/*
  ==========================================================================
  DATA LAYER — konfigurasi, plan, checkpoint, dan lookup table.
  Catatan refactor:
   - VAL_INDEX dinaikkan 50 -> 100 (UI memang memakai index 0..99).
   - struct Plan/CP global yang menduplikasi array runtime DIHAPUS.
     Serialisasi ke SPI Flash kini lewat blob transien (lihat storage.ino).
  ==========================================================================
*/

#include <SPI.h>
#include <SPIMemory.h>
#include <EEPROM.h>

SPIFlash memory(5);              // SPI Flash Winbond 4MB, CS = GPIO5

#define ADCBAT 34
#define LED 12
#define SLED(x) digitalWrite(LED, x)

#define VAL_INDEX  100           // langkah per plan (dulu 50 -> overflow)
#define VAL_PLAN   9             // jumlah plan
#define VAL_CHECKP 8             // checkpoint per plan

#define EEPROM_SIZE 1024

//=================== peta address EEPROM (konfigurasi) =====================
enum address_eeprom {
  addrPlan        = 0,    // 1 byte
  addrNS          = 1,    // 1 byte
  addrSI          = 2,    // 1 byte
  addrCCP         = 3,    // 1 byte
  addrSensSev     = 4,    // 1 byte
  addrsetMaxSensH = 6,    // 14 byte
  addrsetMaxSensL = 20,   // 14 byte
  addrsetMinSensH = 34,   // 14 byte
  addrsetMinSensL = 48,   // 14 byte
  addrCalibH      = 62,   // 14 byte
  addrCalibL      = 76,   // 14 byte
  addrKp          = 90,   // 7 byte
  addrKi          = 97,   // 7 byte
  addrKd          = 104,  // 7 byte
  addrAccelTA     = 111,  // 1 byte
  addrAccelTB     = 112   // 1 byte
};

//=============================== konfigurasi ==============================
uint8_t plan        = 0;
uint8_t normalSpeed = 80;
uint8_t stopIndex   = 0;
uint8_t countCP     = 0;

double Kp[7];
double Ki[7];
double Kd[7];

byte accelTA = 2;   // step ramp fase A (kini benar-benar dipakai di race)
byte accelTB = 2;   // step ramp fase B

//=============================== data plan ===============================
byte    idx       [VAL_PLAN][VAL_INDEX];
byte    logic     [VAL_PLAN][VAL_INDEX];
byte    sensLogIdx[VAL_PLAN][VAL_INDEX];
byte    spdR      [VAL_PLAN][VAL_INDEX];
byte    spdL      [VAL_PLAN][VAL_INDEX];
int16_t idelay    [VAL_PLAN][VAL_INDEX];
int16_t timerA    [VAL_PLAN][VAL_INDEX];
int16_t timerB    [VAL_PLAN][VAL_INDEX];
int16_t speedA    [VAL_PLAN][VAL_INDEX];
int16_t speedB    [VAL_PLAN][VAL_INDEX];
byte    pidProfile[VAL_PLAN][VAL_INDEX];
byte    modeTIM   [VAL_PLAN][VAL_INDEX];
byte    modeSens  [VAL_PLAN][VAL_INDEX];
byte    usedSens  [VAL_PLAN][VAL_INDEX];

//============================ data checkpoint ============================
byte cpAct    [VAL_PLAN][VAL_CHECKP];
byte cpDelay  [VAL_PLAN][VAL_CHECKP];
byte cpTimerA [VAL_PLAN][VAL_CHECKP];
byte cpReadIdx[VAL_PLAN][VAL_CHECKP];

//=============================== lookup ==================================
const unsigned int sensLog[23] = {
  0b11111111111111, 0b00000000000000, 0b00000000000001, 0b10000000000000, 0b00000000000010, 0b01000000000000,
  0b00000000000100, 0b00100000000000, 0b00000000000011, 0b11000000000000, 0b00000000001100, 0b00110000000000,
  0b00000000000111, 0b11100000000000, 0b10000000000001, 0b01000000000010, 0b10000111100000, 0b00000111100001,
  0b11000111100000, 0b00000111100011, 0b11000000000011, 0b11100000000111, 0b11110000001111
};

char logika[4][3]        = {"OR", "AD", "TM", "XR"};
char act[10][10]         = {"STOP", "FORWARD", "LEFT", "RIGHT", "BACKWARD", "PICK", "DROP", "TLEFT", "TRIGHT", "FAN"};
char slctPID[7][9]       = {"Normal", "Profil 1", "Profil 2", "Profil 3", "Profil 4", "Profil 5", "Profil 6"};
char slctMode[3][5]      = {"mS", "CmR", "CmL"};
char slctFLMODE[3][4]    = {"FLC", "FLR", "FLL"};
char slctUsedSens[6][20] = {"All Sensor", "Ignore 1 Side", "Ignore 2 Side", "Ignore 3 Side"};
char actCheckpoint[4][10]= {"FORWARD", "LEFT", "RIGHT", "BACKWARD"};

//=============================== scratch =================================
char buff[100];

#endif // DATA_H
