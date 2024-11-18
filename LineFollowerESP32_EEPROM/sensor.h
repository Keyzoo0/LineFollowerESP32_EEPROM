
#define MUX_Kiri_ADC1 32 
#define MUX_Kanan_ADC2 35
#define S1_MUX 13
#define S2_MUX 14
#define S3_MUX 15 

#define MAXSENSOR 14

uint16_t adcVal[14];
uint16_t CalAdc[14];
uint8_t sensorSensivity;
int16_t maxVal[14];
int16_t minVal[14];
int16_t setMaxVal[14];
int16_t setMinVal[14];


int muxChannel[8][3] = {
  {0, 0, 0},
  {1, 0, 0},
  {0, 1, 0},
  {1, 1, 0},
  {0, 0, 1},
  {1, 0, 1},
  {0, 1, 1},
  {1, 1, 1}
};

bool readSens = false ;

float minBat = 11.8;
  
