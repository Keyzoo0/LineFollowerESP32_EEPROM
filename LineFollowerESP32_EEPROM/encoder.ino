/*
   A -------- B

*/



// void IRAM_ATTR TimerEncoder(){ // timer for calculate RPM
//   portENTER_CRITICAL_ISR(&timerMux);
//   rpmL = pulseL * 6000 / 104;
//   rpmR = pulseR * 6000 / 104 * (-1);
//   pulseL = pulseR = 0;
//   portEXIT_CRITICAL_ISR(&timerMux);
// }

void readENC_A() {
  if (digitalRead(ENC1B) > 0) {
    countEnc_A++;
    pulseL++;
  } else {
    countEnc_A--;
    pulseL--;
  }
}

void readENC_B() {
  if (digitalRead(ENC2B) > 0) {
    countEnc_B++;
    pulseR++;
  } else {
    countEnc_B--;
    pulseR--;
  }
}

void initEncoder(bool state) {
  pinMode(LED, OUTPUT);
  pinMode(ENC1A, INPUT);
  pinMode(ENC1B, INPUT);
  pinMode(ENC2A, INPUT);
  pinMode(ENC2B, INPUT);
  if (state) {
    attachInterrupt(digitalPinToInterrupt(ENC1A), readENC_A, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC2A), readENC_B, RISING);
  } else {
    detachInterrupt(digitalPinToInterrupt(ENC1A));
    detachInterrupt(digitalPinToInterrupt(ENC2A));
  }
}

int measureLengthR(){
  int measure = countEnc_B * factor * (-1);
  if(measure < 0 ){
    countEnc_B = 0;
    return 0 ;
  } else {
    return measure;
  }
}

int measureLengthL(){
  int measure = countEnc_A * factor;
  if(measure < 0 ){
    countEnc_A = 0;
    return 0 ;
  } else {
    return measure;
  }
}
