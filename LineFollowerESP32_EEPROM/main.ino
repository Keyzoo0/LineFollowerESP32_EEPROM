
void setup() {
//setup robot
  Serial.begin(115200);
  setCpuFrequencyMhz(240);
  initDisplay();
  memory.begin();
  setupPID();
  initTimer();
  initEncoder(1);
  setupSensor();
  initMotor();
  initButton();
//read data 
  readCalib();
  readHome();
  read_PID();
  readIdx();
  readMaxMinSens();
  readCP();
  readSensorSens();
  delay(500);
  oledClear();


}

void loop(){
  guiHome();
}