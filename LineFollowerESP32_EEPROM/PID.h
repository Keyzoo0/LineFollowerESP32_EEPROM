int16_t error = 0;
int16_t lastError = 0;
float Kp;
float Ki;
float Kd;
float _Kp[7] =  {6.00, 0.00, 0.00, 0.00, 0.00, 0.00, 7.00};
float _Ki[7] =  {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};;
float _Kd[7] =  {8.10, 0.00, 0.00, 0.00, 0.00, 0.00, 11.00};
double P;
double I;
double D;
double sumError;
unsigned long prevTime;
volatile unsigned long timeNowPID;
double dt;
byte selectPresetPID = 0;
byte selectPresetPIDPlay;


