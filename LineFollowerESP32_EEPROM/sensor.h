#include <SimpleKalmanFilter.h>

#define MUX_Kiri_ADC1 32 
#define MUX_Kanan_ADC2 35
#define S1_MUX 13
#define S2_MUX 14
#define S3_MUX 15 

#define MAXSENSOR 14


hw_timer_t *TimerEncoder_Cfg = NULL;
hw_timer_t *TimerPlay_Cfg = NULL;
hw_timer_t *TimerPID_Cfg = NULL;

uint16_t adcVal[14];
uint16_t CalAdc[14];
uint8_t sensorSensivity;
int16_t maxVal[14];
int16_t minVal[14];
int16_t setMaxVal[14];
int16_t setMinVal[14];

  
