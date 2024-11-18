/*
  //\normal v = 50
   Kp[0] = 3;
   Ki[0] = 0.0;
   Kd[0]= 10;
  // profil 1 v = 80
   Kp[1] = 7.0;
   Ki[1] = 0.02;
   Kd[1]= 12;
  // profil 2 v = 100
   Kp[2] = 7.0;
   Ki[2] = 0.02;
   Kd[2]= 15;
  // profil 3 v = 120
   Kp[3] = 7.4;
   Ki[3] = 0.04;
   Kd[3]= 35;
// profil 4 v = 140
   Kp[4] = 7.4;
   Ki[4] = 0.04;
   Kd[4]= 40;
// profil 5 v = 160
   Kp[5] = 7.4;
   Ki[5] = 0.04;
   Kd[5]= 50;
// profil 6 v = 180
   Kp[6] = 7.4;
   Ki[6] = 0.04;
   Kd[6]= 60;

*/  

int16_t error = 0;
int16_t lastError = 0;

double P;
double I;
double D;
double sumError;
unsigned long prevTime;
volatile unsigned long timeNowPID;
double dt;
byte selectPresetPID = 0;
byte selectPresetPIDPlay = 0;

unsigned long lastProcess = 0;



