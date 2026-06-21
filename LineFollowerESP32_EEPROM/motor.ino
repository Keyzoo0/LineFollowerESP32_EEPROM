// ===========================================================================
// Motor driver (H-bridge BTS7960) — LEDC PWM, core v3.x.
// v2.x: ledcSetup(ch,..) + ledcAttachPin(pin,ch) + ledcWrite(ch,duty)
// v3.x: ledcAttach(pin, freq, res)            + ledcWrite(pin, duty)
// ===========================================================================

void initMotor() {
  ledcAttach(Motor1_A, FREQUENCY, RESOLUTION);
  ledcAttach(Motor1_B, FREQUENCY, RESOLUTION);
  ledcAttach(Motor2_A, FREQUENCY, RESOLUTION);
  ledcAttach(Motor2_B, FREQUENCY, RESOLUTION);
}

void pwmMotor(int pwm1, int pwm2) {   // pwm1 = kiri, pwm2 = kanan
  pwm1 = constrain(pwm1, -255, 255);
  pwm2 = constrain(pwm2, -255, 255);

  if (pwm1 >= 0) {
    ledcWrite(Motor1_A, pwm1);
    ledcWrite(Motor1_B, 0);
  } else {
    ledcWrite(Motor1_A, 0);
    ledcWrite(Motor1_B, -pwm1);
  }

  if (pwm2 >= 0) {
    ledcWrite(Motor2_A, pwm2);
    ledcWrite(Motor2_B, 0);
  } else {
    ledcWrite(Motor2_A, 0);
    ledcWrite(Motor2_B, -pwm2);
  }
}

void speedOne(int spd) { pwmMotor(spd, spd); }

void stopMotor() {
  ledcWrite(Motor1_A, 0);
  ledcWrite(Motor1_B, 0);
  ledcWrite(Motor2_A, 0);
  ledcWrite(Motor2_B, 0);
}

void stopMotorL() {
  ledcWrite(Motor1_A, 0);
  ledcWrite(Motor1_B, 0);
}

void stopMotorR() {
  ledcWrite(Motor2_A, 0);
  ledcWrite(Motor2_B, 0);
}
