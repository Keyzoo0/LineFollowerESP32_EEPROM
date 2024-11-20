
#include <SPI.h> // ini untuk memori external 
#include <SPIMemory.h>
#include <EEPROM.h>

SPIFlash memory(5);


#define ADCBAT 34
#define LED 12
#define SLED(x) digitalWrite(LED, x)

#define VAL_INDEX 50
#define VAL_PLAN 9
#define VAL_CHECKP 8

/*
  BISMILLAHHIRAHMANIRAHIM G15 ORA KAGET!!!!!
   LIHAT ADDRESSNYA !!!!!!!!!!!

  //===========plan dan checkpoint di simpan di spi memory winbond 4mb

  // Satu Plan ada 18 Parameter 100 byte yang disimpan jadi 18*100 = 1800 Addr yang dipake per plan
  // karena ada 10 plan maka terpakai address sampai 18000 byte
  // Satu CP ada 4 Parameter 8 byte yang disimpan jadi 4*8 = 32 Addr yang dipake per plan
  // karena ada 8 checkpoint maka terpakai address sampai 256 byte
  // checkpoint di simpan di setelah base address semua plan
  // noted : 
  // sekarang total address yang terpakai total : 18256 byte 
  // jika ingin menambah address dan lebih dari 32000 address ganti eraseblock32k(0) di fungsi saveAll menjadi eraseblock64k(0)

  //============data di simpan di eeprom

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


*/

//=============================data yang disimpan di eeprom ========================================
enum address_eeprom{
  addrPlan = 0 , // 1 byte
  addrNS = 1 , // 1 byte 
  addrSI = 2 , // 1 byte
  addrCCP = 3 , // 1 byte 
  addrSensSev = 4 , // 1 byte
  // = 5 ,// 1 byte
  addrsetMaxSensH = 6 , // 14 byte
  addrsetMaxSensL = 20 , // 14 byte
  addrsetMinSensH = 34 , // 14 byte
  addrsetMinSensL = 48, // 14 byte
  addrCalibH = 62 , // 14 byte
  addrCalibL = 76,  //14 byte
  addrKp = 90 , // 7 byte 
  addrKi = 97 , // 7 byte 
  addrKd = 104 // 7 byte 
  //104
};

//data threshold calib sensor
uint8_t value[14];
uint8_t H[14];
uint8_t L[14];
uint8_t MaxSensH[14];
uint8_t MaxSensL[14];
uint8_t MinSensH[14];
uint8_t MinSensL[14];


double Kp[7] ;
double Ki[7] ;
double Kd[7] ;

uint8_t _Kp[7];
uint8_t _Ki[7];
uint8_t _Kd[7];




//======================================data plan ====================================================
// Struct untuk Plan (Plan)


typedef struct {
    uint8_t saveIdx[VAL_INDEX];
    uint8_t savelogic[VAL_INDEX];
    uint8_t savesensLogIdx[VAL_INDEX];
    uint8_t savetrigW[VAL_INDEX];
    uint8_t savespdR[VAL_INDEX];
    uint8_t savespdL[VAL_INDEX];
    uint8_t saveidelayH[VAL_INDEX];  // idelay High 
    uint8_t saveidelayL[VAL_INDEX];  // idelay Low
    uint8_t savetimerAH[VAL_INDEX];  // TA High
    uint8_t savetimerAL[VAL_INDEX];  // TA Low
    uint8_t savetimerBH[VAL_INDEX];  // TB High
    uint8_t savetimerBL[VAL_INDEX];  // TB Low
    uint8_t savespeedA[VAL_INDEX];
    uint8_t savespeedB[VAL_INDEX];
    uint8_t saveclrLine[VAL_INDEX];
    uint8_t saveprofilePID[VAL_INDEX];
    uint8_t saveModeTIM[VAL_INDEX];
    uint8_t saveModeSens[VAL_INDEX];
    uint8_t saveUsedSens[VAL_INDEX];
} Plans;

// Array of Plans structs
Plans Plan[VAL_PLAN];  // Reduced to 2 for testing memory limits


//=================================data check point ===============================================
#define VAL_CHECKP 8

// Struct untuk Checkpoint (CP)
typedef struct  {
    uint8_t saveAct[VAL_CHECKP];
    uint8_t saveiDelay[VAL_CHECKP];
    uint8_t savetimerA[VAL_CHECKP];
    uint8_t saveReadIdx[VAL_CHECKP];
}Checkpoints;

Checkpoints CP[VAL_PLAN];

//=============home logic=============================
char buff[100];
int valueSensor[14];
int sens;
bool stateIdxM = false;
bool stateRun = false;

//==========setting checkpoint===========================

byte checkPoint[VAL_PLAN][VAL_CHECKP];
byte readCCheckpoint[VAL_PLAN][VAL_CHECKP];
byte timerACheckpoint[VAL_PLAN][VAL_CHECKP];
byte iDelayCheckpoint[VAL_PLAN][VAL_CHECKP];
byte readIdxCheckpoint[VAL_PLAN][VAL_CHECKP];
char actCheckpoint[4][10] = {"FORWARD", "LEFT", "RIGHT", "BACKWARD"};

//============setting index===============================
uint8_t plan ;
uint8_t normalSpeed ;
uint8_t stopIndex ;
uint8_t countCP ;  // Misalnya tambahan variabel yang ingin disimpan
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
byte modeSens[VAL_PLAN][VAL_INDEX];
byte usedSens[VAL_PLAN][VAL_INDEX];


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
char slctUsedSens[6][20] = {"All Sensor" , "Ignore 1 Side" , "Ignore 2 Side" , "Ignore 3 Side" };


//===========throttle====================
byte accelTA = 2,
     accelTB = 2 ;  

//========save and read memory===


//================ save and read plan========================
void saveAllPlans() {
    for (uint8_t planIndex = 0; planIndex < VAL_PLAN; planIndex++) {
        for (uint8_t i = 0; i < VAL_INDEX; i++) {
            SLED(0);
            // Populate plan data
            Plan[planIndex].saveIdx[i] = idx[planIndex][i];
            Plan[planIndex].savelogic[i] = logic[planIndex][i];
            Plan[planIndex].savesensLogIdx[i] = sensLogIdx[planIndex][i];
            Plan[planIndex].savetrigW[i] = trigW[planIndex][i];
            Plan[planIndex].savespdR[i] = spdR[planIndex][i];
            Plan[planIndex].savespdL[i] = spdL[planIndex][i];
            Plan[planIndex].saveidelayH[i] = idelay[planIndex][i] >> 8;
            Plan[planIndex].saveidelayL[i] = idelay[planIndex][i] & 0x00ff;
            Plan[planIndex].savetimerAH[i] = timerA[planIndex][i] >> 8;
            Plan[planIndex].savetimerAL[i] = timerA[planIndex][i] & 0x00ff;
            Plan[planIndex].savetimerBH[i] = timerB[planIndex][i] >> 8;
            Plan[planIndex].savetimerBL[i] = timerB[planIndex][i] & 0x00ff;
            Plan[planIndex].savespeedA[i] = speedA[planIndex][i];
            Plan[planIndex].savespeedB[i] = speedB[planIndex][i];
            Plan[planIndex].saveclrLine[i] = clrLine[planIndex][i];
            Plan[planIndex].saveprofilePID[i] = pidProfile[planIndex][i];
            Plan[planIndex].saveModeTIM[i] = modeTIM[planIndex][i];
            Plan[planIndex].saveModeSens[i] = modeSens[planIndex][i]; 
            Plan[planIndex].saveUsedSens[i] = usedSens[planIndex][i]; 
            SLED(1);
        }

        uint16_t planAddr = planIndex * sizeof(Plan[planIndex]);
        
        memory.writeByteArray(planAddr , (uint8_t*)&Plan[planIndex], sizeof(Plan[planIndex]));

    }
}

void readIdx() {
    for (uint8_t planIndex = 0; planIndex < 5; planIndex++) { // Loop untuk 5 plan
        memory.readByteArray(planIndex * sizeof(Plan[planIndex]), (uint8_t*)&Plan[planIndex], sizeof(Plan[planIndex]));
        for (uint8_t i = 0; i < VAL_INDEX; i++) {
            idx[planIndex][i] = Plan[planIndex].saveIdx[i];
            logic[planIndex][i] = Plan[planIndex].savelogic[i];
            sensLogIdx[planIndex][i] = Plan[planIndex].savesensLogIdx[i];
            trigW[planIndex][i] = Plan[planIndex].savetrigW[i];
            spdR[planIndex][i] = Plan[planIndex].savespdR[i];
            spdL[planIndex][i] = Plan[planIndex].savespdL[i];
            idelay[planIndex][i] = (Plan[planIndex].saveidelayH[i] << 8) | Plan[planIndex].saveidelayL[i];
            timerA[planIndex][i] = (Plan[planIndex].savetimerAH[i] << 8) | Plan[planIndex].savetimerAL[i];
            timerB[planIndex][i] = (Plan[planIndex].savetimerBH[i] << 8) | Plan[planIndex].savetimerBL[i];
            speedA[planIndex][i] = Plan[planIndex].savespeedA[i];
            speedB[planIndex][i] = Plan[planIndex].savespeedB[i];
            clrLine[planIndex][i] = Plan[planIndex].saveclrLine[i];
            pidProfile[planIndex][i] = Plan[planIndex].saveprofilePID[i];
            modeTIM[planIndex][i] = Plan[planIndex].saveModeTIM[i];
            modeSens[planIndex][i]= Plan[planIndex].saveModeSens[i] ; 
            usedSens[planIndex][i]= Plan[planIndex].saveUsedSens[i] ; 

        }
    }
}

//===================save and read cheack point ==================================

void  saveAllCheckPoints(){

    for (uint8_t cpIndex = 0; cpIndex < VAL_PLAN; cpIndex++) {
        uint16_t cpAddr = (sizeof(Plan[0])*VAL_PLAN) + sizeof(CP[cpIndex])*cpIndex;
        memory.writeByteArray(cpAddr , (uint8_t*)&CP[cpIndex], sizeof(CP[cpIndex]));

        for (uint8_t i = 0; i < VAL_CHECKP; i++) {
            SLED(0);
            readCCheckpoint[cpIndex][i] = CP[cpIndex].saveAct[i];
            iDelayCheckpoint[cpIndex][i] = CP[cpIndex].saveiDelay[i];
            timerACheckpoint[cpIndex][i] = CP[cpIndex].savetimerA[i];
            readIdxCheckpoint[cpIndex][i] = CP[cpIndex].saveReadIdx[i];
            SLED(1);
        }
    }
}

void readCP(){
    for (uint8_t cpIndex = 0; cpIndex < VAL_PLAN; cpIndex++) {
        for (uint8_t i = 0; i < VAL_CHECKP; i++) {
            SLED(0);
            CP[cpIndex].saveAct[i] = readCCheckpoint[cpIndex][i];
            CP[cpIndex].saveiDelay[i] = iDelayCheckpoint[cpIndex][i];
            CP[cpIndex].savetimerA[i] = timerACheckpoint[cpIndex][i];
            CP[cpIndex].saveReadIdx[i] = readIdxCheckpoint[cpIndex][i];
            SLED(1);
        }
        uint16_t cpAddr = (sizeof(Plan[0])*VAL_PLAN) + sizeof(CP[cpIndex])*cpIndex;

        
        memory.readByteArray(cpAddr , (uint8_t*)&CP[cpIndex], sizeof(CP[cpIndex]));

    }
     
}

//====================================read pid ===================================

void readPID(){
  for(int i = 0 ; i < 7 ; i++){
  _Kp[i] = EEPROM.read(addrKp + i);
  _Ki[i] = EEPROM.read(addrKi + i);
  _Kd[i] = EEPROM.read(addrKd + i);
  
  Kp[i] = (float)(_Kp[i] * pow(10 , -1));
  Ki[i] = (float)(_Ki[i] * pow(10 , -2));
  Kd[i] = (float)_Kd[i] ;

  }

}


void savePID(){
  
  for(int i = 0 ; i < 7 ; i++){
  _Kp[i]  = (uint8_t)(Kp[i]  * pow(10 , 1)) ;
  _Ki[i]  = (uint8_t)(Ki[i] * pow(10 , 2)) ;
  _Kd[i]  = (uint8_t)Kd[i] ;

     EEPROM.write(addrKp + i , _Kp[i]);
     EEPROM.write(addrKi + i , _Ki[i]);
     EEPROM.write(addrKd + i , _Kd[i]);
  }
  EEPROM.commit();

}

//==============================read and save home =======================================================
void saveHome() { 
  EEPROM.write(0 , plan);
  EEPROM.write(1 , normalSpeed);
  EEPROM.write(2 , stopIndex);
  EEPROM.write(3 , countCP);
  
  EEPROM.commit();
}


void readHome() {
  
   plan = EEPROM.read(addrPlan) ;
   normalSpeed =  EEPROM.read(addrNS) ;
   stopIndex =  EEPROM.read(addrSI) ;
   countCP =  EEPROM.read(addrCCP) ;

}


//=========================read and save calib====================================
void readCalib(){
  for(uint8_t i = 0; i < 14; i++){
    H[i] = EEPROM.read(addrCalibH + i);
    L[i] = EEPROM.read(addrCalibL + i);
    CalAdc[i] = H[i]<<8 | (L[i] & 0x00ff);  
  }
}



void saveCalib(){
  for(uint8_t i = 0; i < MAXSENSOR; i++){
    value[i] = CalAdc[i];
    H[i] = value[i]>>8;
    L[i] = value[i] & 0x00ff;
    EEPROM.write(addrCalibH + i , H[i]);
    EEPROM.write(addrCalibL + i , L[i]);
  }
  EEPROM.commit();

}


//==================== read and save MaxMinSens ========================================== 

void saveMaxMinSens(){
  for(uint8_t i = 0; i < MAXSENSOR; i++){
    MaxSensH[i] = setMaxVal[i] >> 8;
    MaxSensL[i] = setMaxVal[i] & 0x00ff;
    MinSensH[i] = setMinVal[i] >> 8;
    MinSensL[i] = setMinVal[i] & 0x00ff;
  }
   for(int i = 0 ; i < 14 ; i++){ // data sens sensor 14 byte
    EEPROM.write(addrsetMaxSensH + i , MaxSensH[i] );
    EEPROM.write(addrsetMaxSensL + i , MaxSensL[i] );
    EEPROM.write(addrsetMinSensH + i , MinSensH[i] );
    EEPROM.write(addrsetMinSensL + i , MinSensL[i] );
  }
  EEPROM.commit();
}



void readMaxMinSens(){
  for(int i = 0 ; i < 14 ; i++){ // data sens sensor 14 byte
    MaxSensH[i] = EEPROM.read(addrsetMaxSensH + i );
    MaxSensL[i] = EEPROM.read(addrsetMaxSensL + i );
    MinSensH[i] = EEPROM.read(addrsetMinSensH + i );
    MinSensL[i] = EEPROM.read(addrsetMinSensL + i );
  }
  for(uint8_t i = 0; i < MAXSENSOR; i++){
    setMaxVal[i] = MaxSensH[i] << 8 | (MaxSensL[i] & 0x00ff);
    setMinVal[i] = MinSensH[i] << 8 | (MinSensL[i] & 0x00ff);
  }
}


// ================================= read and save sensor sensitivity ============================================
void readSensorSens(){
  sensorSensivity = EEPROM.read(addrSensSev);
}

void saveSensorSens(){
  EEPROM.write(addrSensSev , sensorSensivity );
  EEPROM.commit();
}



// =====================================save all===================================================



void saveAll() {
  SLED(1);
  memory.eraseBlock32K(0); 
  saveAllPlans();
  saveAllCheckPoints();
  SLED(0);
}

void readAll(){
  readHome();
  readCP();
  readIdx();
  readSensorSens();
  readMaxMinSens();
  readCalib();
  readPID();
  
}

//=========================setup memory ==============================================
void setupMemory(){
  memory.begin();
  EEPROM.begin(1023);
  readAll();
}

