
//Linking all header 
#include "oled.h"
#include "button.h"
#include "encoder.h"
#include "motor.h"
#include "sensor.h"
#include "gui.h"
#include "PID.h"
#include "memory.h"
#include "kinematika.h"
#include "timer.h"

void setup() {
//setup robot
  // Serial.begin(115200);
  initDisplay();
  setCpuFrequencyMhz(240);
  initEncoder(0);
  setupSensor();
  initMotor();
  initButton();
  setupMemory();
  delay(100); 
  oledClear(); 
}

void loop(){
  guiHome();
}