
void initMotor() {
  ledcSetup(Motor1_A_CH, FREQUENCY, RESOULTION);
  ledcSetup(Motor1_B_CH, FREQUENCY, RESOULTION);
  ledcSetup(Motor2_A_CH, FREQUENCY, RESOULTION);
  ledcSetup(Motor2_B_CH, FREQUENCY, RESOULTION);

  ledcAttachPin(Motor1_A, Motor1_A_CH);
  ledcAttachPin(Motor1_B, Motor1_B_CH);
  ledcAttachPin(Motor2_A, Motor2_A_CH);
  ledcAttachPin(Motor2_B, Motor2_B_CH);
}

void speedOne(int spd){
  pwmMotor(spd, spd);
}

void pwmMotor(int pwm1, int pwm2) { // Kiri, Kanan
  if (pwm1 > 255) pwm1 = 255;
  else if (pwm1 < -255) pwm1 = -255;

  if (pwm1 > 0) {
    ledcWrite(Motor1_A_CH, pwm1);
    ledcWrite(Motor1_B_CH, 0);
  } else if (pwm1 < 0) {
    ledcWrite(Motor1_A_CH, 0);
    ledcWrite(Motor1_B_CH, abs(pwm1) );
  }
  
  if (pwm2 > 0) {
    ledcWrite(Motor2_A_CH, pwm2);
    ledcWrite(Motor2_B_CH, 0);
  } else if (pwm2 < 0) {
    ledcWrite(Motor2_A_CH, 0);
    ledcWrite(Motor2_B_CH, abs(pwm2));
  }
}

void stopMotor() {
  ledcWrite(Motor1_A_CH, 0);
  ledcWrite(Motor1_B_CH, 0);
  ledcWrite(Motor2_A_CH, 0);
  ledcWrite(Motor2_B_CH, 0);
}

void stopMotorL() {
  ledcWrite(Motor1_A_CH, 0);
  ledcWrite(Motor1_B_CH, 0);
}

void stopMotorR() {
  ledcWrite(Motor2_A_CH, 0);
  ledcWrite(Motor2_B_CH, 0);
}
