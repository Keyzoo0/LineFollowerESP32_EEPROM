#ifndef BUTTON_H 
#define BUTTON_H 

#include <Adafruit_PCF8574.h> // ini untuk button 
#include <Wire.h> 

Adafruit_PCF8574 pcf;

#define PCF8574_ADDR 0x27
#define Button_OK 5
#define Button_UP 3
#define Button_DOWN 4
#define Button_RUN 2
#define Button_PLUS 0
#define Button_MIN 1


#define btnOk     Button_OK
#define btnUp     Button_UP
#define btnDown   Button_DOWN
#define btnBack   Button_RUN
#define btnPlus   Button_PLUS
#define btnMinus  Button_MIN



#define LONG_TIME_PRESS 1000
bool currentStatePress;
bool lastStatePress = false;
unsigned long pressTime;
unsigned long releaseTime;
#define LED_PIN 12


#endif
