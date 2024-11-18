
#define ENC1A 33
#define ENC1B 25
#define ENC2A 39
#define ENC2B 36

int16_t countEnc_A;
int16_t countEnc_B;
int16_t rpmR, rpmL;
int16_t pulseL;
int16_t pulseR;
unsigned long lastTimeRPM;

#define CPR 208
#define DiameterRoda 17 // satuan mm
float factor = (PI * DiameterRoda) / (CPR);
