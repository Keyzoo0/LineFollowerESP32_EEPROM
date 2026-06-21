#ifndef INPUT_H
#define INPUT_H

// ===========================================================================
// Input NON-BLOCKING — baca 6 tombol via PCF8574 sekali per frame, hasilkan
// event edge/repeat. Tidak ada busy-wait menunggu tombol dilepas.
// ===========================================================================

#include <Adafruit_PCF8574.h>
#include <Wire.h>

Adafruit_PCF8574 pcf;
#define PCF8574_ADDR 0x27
#define LED_PIN 12

#define NBTN 6
enum { BTN_OK = 0, BTN_UP, BTN_DOWN, BTN_BACK, BTN_PLUS, BTN_MIN };

// pemetaan index logis -> pin PCF8574
const uint8_t pcfPin[NBTN] = { 5, 3, 4, 2, 0, 1 };

// hasil event (di-refresh tiap inputUpdate)
bool kDown[NBTN];      // sedang ditekan (sudah didebounce)
bool kPressed[NBTN];   // rising edge frame ini
bool kReleased[NBTN];  // falling edge frame ini
bool kRepeat[NBTN];    // edge ATAU tick auto-repeat (untuk tombol +/-)

#define DEBOUNCE_MS  25
#define REPEAT_DELAY 350
#define REPEAT_RATE  110

#endif // INPUT_H
