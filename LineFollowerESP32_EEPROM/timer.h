#include "Arduino.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"

portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

hw_timer_t *Timer0_Encoder = NULL;
hw_timer_t *Timer1_Play = NULL;
hw_timer_t *Timer2_PID = NULL;
