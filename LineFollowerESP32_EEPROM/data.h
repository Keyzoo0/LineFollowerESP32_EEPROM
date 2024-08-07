#ifndef __DATA__H
#define __DATA__H


#define ADCBAT 34
#define LED 12
#define SLED(x) digitalWrite(LED, x)

#define VAL_INDEX 100
#define VAL_PLAN 5
#define VAL_CHECKP 8



/*
   LIHAT ADDRESSNYA !!!!!!!!!!!
   0 = Address HomeScreen
   8 = Address Sensor Calibration A
   23 = Address Sensor Calibration B
   38 = Address Sensor Sensivity
   39 - 43 = addr Kp <- 4 Byte (karena float)
   44 - 48 = addr Ki 
   49 - 53 = addr Kd 
   54 = Addr Max Sensor High
   55 = Addr Max Sensor Low
   56 = Addr Min Sensor High
   57 = Addr Min Sensor Low
   4100 - 5700 = P1 IDx
   5800 - 7300 = P2 IDx
   7400 - 8800 = P3 IDx
   8900 - 10300 = P4 IDx
   10400 - 11800 = P5 IDx

   

   // Satu Plan ada 17 Parameter yang disimpan jadi 17*100 = 1700 Addr yang dipake per plan
   // Satu CP ada 4 Parameter
*/

#define addrHome 0
#define addrCalibA 8
#define addrCalibB 23
#define addrSensSev 38
#define addrKp 39 // 4 Byte
#define addrKi 44 // 4 Byte
#define addrKd 49 // 4 Byte
#define addrsetMaxSensH 54 // 14 Data
#define addrsetMaxSensL 68 // 14 Data
#define addrsetMinSensH 82 // 14 Data
#define addrsetMinSensL 96 // 14 Data
#define addr_Kp(x) x*4+100
#define addr_Kd(x) x*4+130

#define addrCountIdxP1(x) (x*VAL_INDEX) + 4000
#define addrCountIdxP2(x) (x*VAL_INDEX) + 5800
#define addrCountIdxP3(x) (x*VAL_INDEX) + 7400
#define addrCountIdxP4(x) (x*VAL_INDEX) + 8900
#define addrCountIdxP5(x) (x*VAL_INDEX) + 10400

#define addrACTCP1 17300
#define addrtimerACP1 17310
#define addridelayCP1 17320
#define addrIdxCP1 17330

#define addrACTCP2 17340
#define addrtimerACP2 17350
#define addridelayCP2 17360
#define addrIdxCP2 17370

#define addrACTCP3 17380
#define addrtimerACP3 17390
#define addridelayCP3 17400
#define addrIdxCP3 17410

#define addrACTCP4 17420
#define addrtimerACP4 17430
#define addridelayCP4 17440
#define addrIdxCP4 17450

#define addrACTCP5 17460
#define addrtimerACP5 17470
#define addridelayCP5 17480
#define addrIdxCP5 17490

int value[14];
byte H[14];
byte L[14];
uint8_t _valDumpHome[8];
uint8_t _saveHomeScreen[8];
byte MaxSensH[14];
byte MaxSensL[14];
byte MinSensH[14];
byte MinSensL[14];

// CP P1
uint8_t _saveActCPP1[VAL_CHECKP];
uint8_t _saveiDelayCPP1[VAL_CHECKP];
uint8_t _savetimerACPP1[VAL_CHECKP];
uint8_t _saveReadIdxCPP1[VAL_CHECKP];

// CP P2
uint8_t _saveActCPP2[VAL_CHECKP];
uint8_t _saveiDelayCPP2[VAL_CHECKP];
uint8_t _savetimerACPP2[VAL_CHECKP];
uint8_t _saveReadIdxCPP2[VAL_CHECKP];

// CP P3
uint8_t _saveActCPP3[VAL_CHECKP];
uint8_t _saveiDelayCPP3[VAL_CHECKP];
uint8_t _savetimerACPP3[VAL_CHECKP];
uint8_t _saveReadIdxCPP3[VAL_CHECKP];

// CP P4
uint8_t _saveActCPP4[VAL_CHECKP];
uint8_t _saveiDelayCPP4[VAL_CHECKP];
uint8_t _savetimerACPP4[VAL_CHECKP];
uint8_t _saveReadIdxCPP4[VAL_CHECKP];

// CP P5
uint8_t _saveActCPP5[VAL_CHECKP];
uint8_t _saveiDelayCPP5[VAL_CHECKP];
uint8_t _savetimerACPP5[VAL_CHECKP];
uint8_t _saveReadIdxCPP5[VAL_CHECKP];

// P1
uint8_t _saveIdxP1[VAL_INDEX];
uint8_t _savelogicP1[VAL_INDEX];
uint8_t _savesensLogIdxP1[VAL_INDEX];
uint8_t _savetrigWP1[VAL_INDEX];
uint8_t _savespdRP1[VAL_INDEX];
uint8_t _savespdLP1[VAL_INDEX];
uint8_t _saveidelayP1H[VAL_INDEX]; // idelay High 
uint8_t _saveidelayP1L[VAL_INDEX]; // idelay LOW
uint8_t _savetimerAP1H[VAL_INDEX]; // TA HIGH
uint8_t _savetimerAP1L[VAL_INDEX]; // TA LOW
uint8_t _savetimerBP1H[VAL_INDEX]; // TB HIGH
uint8_t _savetimerBP1L[VAL_INDEX]; // TB LOW
uint8_t _savespeedAP1[VAL_INDEX];
uint8_t _savespeedBP1[VAL_INDEX];
uint8_t _saveclrLineP1[VAL_INDEX];
uint8_t _saveprofilePIDP1[VAL_INDEX];
uint8_t _saveModeTIMP1[VAL_INDEX];

// P2
uint8_t _saveIdxP2[VAL_INDEX];
uint8_t _savelogicP2[VAL_INDEX];
uint8_t _savesensLogIdxP2[VAL_INDEX];
uint8_t _savetrigWP2[VAL_INDEX];
uint8_t _savespdRP2[VAL_INDEX];
uint8_t _savespdLP2[VAL_INDEX];
uint8_t _saveidelayP2H[VAL_INDEX]; // idelay High 
uint8_t _saveidelayP2L[VAL_INDEX]; // idelay LOW
uint8_t _savetimerAP2H[VAL_INDEX]; // TA HIGH
uint8_t _savetimerAP2L[VAL_INDEX]; // TA LOW
uint8_t _savetimerBP2H[VAL_INDEX]; // TB HIGH
uint8_t _savetimerBP2L[VAL_INDEX]; // TB LOW
uint8_t _savespeedAP2[VAL_INDEX];
uint8_t _savespeedBP2[VAL_INDEX];
uint8_t _saveclrLineP2[VAL_INDEX];
uint8_t _saveprofilePIDP2[VAL_INDEX];
uint8_t _saveModeTIMP2[VAL_INDEX];

// P3
uint8_t _saveIdxP3[VAL_INDEX];
uint8_t _savelogicP3[VAL_INDEX];
uint8_t _savesensLogIdxP3[VAL_INDEX];
uint8_t _savetrigWP3[VAL_INDEX];
uint8_t _savespdRP3[VAL_INDEX];
uint8_t _savespdLP3[VAL_INDEX];
uint8_t _saveidelayP3H[VAL_INDEX]; // idelay High 
uint8_t _saveidelayP3L[VAL_INDEX]; // idelay LOW
uint8_t _savetimerAP3H[VAL_INDEX]; // TA HIGH
uint8_t _savetimerAP3L[VAL_INDEX]; // TA LOW
uint8_t _savetimerBP3H[VAL_INDEX]; // TB HIGH
uint8_t _savetimerBP3L[VAL_INDEX]; // TB LOW
uint8_t _savespeedAP3[VAL_INDEX];
uint8_t _savespeedBP3[VAL_INDEX];
uint8_t _saveclrLineP3[VAL_INDEX];
uint8_t _saveprofilePIDP3[VAL_INDEX];
uint8_t _saveModeTIMP3[VAL_INDEX];

// P4
uint8_t _saveIdxP4[VAL_INDEX];
uint8_t _savelogicP4[VAL_INDEX];
uint8_t _savesensLogIdxP4[VAL_INDEX];
uint8_t _savetrigWP4[VAL_INDEX];
uint8_t _savespdRP4[VAL_INDEX];
uint8_t _savespdLP4[VAL_INDEX];
uint8_t _saveidelayP4H[VAL_INDEX]; // idelay High 
uint8_t _saveidelayP4L[VAL_INDEX]; // idelay LOW
uint8_t _savetimerAP4H[VAL_INDEX]; // TA HIGH
uint8_t _savetimerAP4L[VAL_INDEX]; // TA LOW
uint8_t _savetimerBP4H[VAL_INDEX]; // TB HIGH
uint8_t _savetimerBP4L[VAL_INDEX]; // TB LOW
uint8_t _savespeedAP4[VAL_INDEX];
uint8_t _savespeedBP4[VAL_INDEX];
uint8_t _saveclrLineP4[VAL_INDEX];
uint8_t _saveprofilePIDP4[VAL_INDEX];
uint8_t _saveModeTIMP4[VAL_INDEX];

// P5
uint8_t _saveIdxP5[VAL_INDEX];
uint8_t _savelogicP5[VAL_INDEX];
uint8_t _savesensLogIdxP5[VAL_INDEX];
uint8_t _savetrigWP5[VAL_INDEX];
uint8_t _savespdRP5[VAL_INDEX];
uint8_t _savespdLP5[VAL_INDEX];
uint8_t _saveidelayP5H[VAL_INDEX]; // idelay High 
uint8_t _saveidelayP5L[VAL_INDEX]; // idelay LOW
uint8_t _savetimerAP5H[VAL_INDEX]; // TA HIGH
uint8_t _savetimerAP5L[VAL_INDEX]; // TA LOW
uint8_t _savetimerBP5H[VAL_INDEX]; // TB HIGH
uint8_t _savetimerBP5L[VAL_INDEX]; // TB LOW
uint8_t _savespeedAP5[VAL_INDEX];
uint8_t _savespeedBP5[VAL_INDEX];
uint8_t _saveclrLineP5[VAL_INDEX];
uint8_t _saveprofilePIDP5[VAL_INDEX];
uint8_t _saveModeTIMP5[VAL_INDEX];

//=============home logic=============================
char buff[100];
int valueSensor[14];
int sens;
bool stateIdxM = false;
bool stateRun = false;

//==========setting checkpoint===========================
#define VAL_CHECKP 8
byte countCP;
byte checkPoint[VAL_PLAN][VAL_CHECKP];
byte readCCheckpoint[VAL_PLAN][VAL_CHECKP];
byte timerACheckpoint[VAL_PLAN][VAL_CHECKP];
byte iDelayCheckpoint[VAL_PLAN][VAL_CHECKP];
byte readIdxCheckpoint[VAL_PLAN][VAL_CHECKP];
char actCheckpoint[4][10] = {"FORWARD", "LEFT", "RIGHT", "BACKWARD"};

//============setting index===============================
uint8_t normalSpeed;
uint8_t plan;
uint8_t stopIndex;
byte countIdx;
byte idx[VAL_PLAN][VAL_INDEX];
byte logic[VAL_PLAN][VAL_INDEX];
byte sensLogIdx[VAL_PLAN][VAL_INDEX];
byte trigW[VAL_PLAN][VAL_INDEX];
byte spdR[VAL_PLAN][VAL_INDEX];
byte spdL[VAL_PLAN][VAL_INDEX];
int16_t idelay[VAL_PLAN][VAL_INDEX];
int16_t timerA[VAL_PLAN][VAL_INDEX];
int16_t timerB[VAL_PLAN][VAL_INDEX];
int16_t speedA[VAL_PLAN][VAL_INDEX];
int16_t speedB[VAL_PLAN][VAL_INDEX];
byte clrLine[VAL_PLAN][VAL_INDEX];
byte pidProfile[VAL_PLAN][VAL_INDEX];
byte modeTIM[VAL_PLAN][VAL_INDEX];

const unsigned int sensLog[23] {
  0b11111111111111, 0b00000000000000, 0b00000000000001, 0b10000000000000, 0b00000000000010, 0b01000000000000,
  0b00000000000100, 0b00100000000000, 0b00000000000011, 0b11000000000000, 0b00000000001100, 0b00110000000000,
  0b00000000000111, 0b11100000000000, 0b10000000000001, 0b01000000000010, 0b10000111100000, 0b00000111100001,
  0b11000111100000, 0b00000111100011, 0b11000000000011, 0b11100000000111, 0b11110000001111
};
char logika[4][3] = {"OR", "AD", "TM", "XR"};
char slctTrig[2][3] = {"MT", "LN"};
char act[10][10] = {"STOP", "FORWARD", "LEFT", "RIGHT", "BACKWARD", "PICK", "DROP", "TLEFT", "TRIGHT", "FAN"};
char clrLineI[2][6] = {"Black", "White"};
char slctPID[7][9] = {"Normal", "Profil 1", "Profil 2", "Profil 3", "Profil 4", "Profil 5", "Profil 6"};
char slctMode[3][5] = {"mS", "CmR", "CmL"};
char slctFLMODE[3][4] = {"FLC", "FLR", "FLL"};

//========= mapping 2 value =================

double _base, _factor;

double inline map2(const double value, double _inMin, double _inMax, double _outMin, double _outMax) {
  double _inRange = _inMax - _inMin;
  double _outRange = _outMax - _outMin;
  if (_inRange == 0.0 || _outRange == 0.0) return 0;

  _factor = _outRange / _inRange;
  _base = _outMin - _inMin * _factor;

  if ( value <= _inMin ) return _outMin;
  if ( value >= _inMax ) return _outMax;

  return _base + value * _factor;
}



#endif