#ifndef PID_H
#define PID_H

/*
  Preset PID acuan (disimpan/diedit lewat menu Tune PID):
    Normal   v50  : Kp 3.0  Ki 0.00  Kd 10
    Profil 1 v80  : Kp 7.0  Ki 0.02  Kd 12
    Profil 2 v100 : Kp 7.0  Ki 0.02  Kd 15
    Profil 3 v120 : Kp 7.4  Ki 0.04  Kd 35
    Profil 4 v140 : Kp 7.4  Ki 0.04  Kd 40
    Profil 5 v160 : Kp 7.4  Ki 0.04  Kd 50
    Profil 6 v180 : Kp 7.4  Ki 0.04  Kd 60
*/

int16_t error     = 0;
int16_t lastError = 0;
double  P, I, D;
double  sumError = 0;

#endif // PID_H
