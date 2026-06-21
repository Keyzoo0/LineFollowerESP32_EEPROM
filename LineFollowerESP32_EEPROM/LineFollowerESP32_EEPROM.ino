// ===========================================================================
// Robot Line Follower ESP32 — EEPROM Polinema
// Arsitektur NON-BLOCKING (cooperative): loop() = input -> handle -> render.
// Kompatibel Arduino-ESP32 core v3.x.
// ===========================================================================

#include "oled.h"     // display SH1106 + bitmap + helper gambar
#include "input.h"    // tombol non-blocking (PCF8574)
#include "encoder.h"
#include "motor.h"    // LEDC v3.x
#include "sensor.h"
#include "PID.h"
#include "data.h"     // konfigurasi + plan + checkpoint + lookup
#include "timer.h"    // StopWatch
#include "ui.h"       // state machine layar

#define FRAME_MS 33                 // ~30 fps render
static unsigned long lastFrame = 0;

void setup() {
  Wire.begin();
  initDisplay();
  setCpuFrequencyMhz(240);
  initEncoder(0);
  setupSensor();
  initMotor();
  initInput();
  setupStorage();
  delay(100);
  oledClear();
  enterScreen(SCR_HOME);
}

void loop() {
  inputUpdate();                    // baca tombol sekali per frame (non-blocking)
  uiHandle();                       // logika layar aktif
  if (millis() - lastFrame >= FRAME_MS) {
    lastFrame = millis();
    uiRender();                     // satu lcd.display() per frame
  }
}
