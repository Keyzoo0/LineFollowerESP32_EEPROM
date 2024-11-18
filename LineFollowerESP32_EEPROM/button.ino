// #include "button.h"
void initButton() {
  pcf.begin(PCF8574_ADDR, &Wire);
  pcf.pinMode(0, INPUT_PULLUP);
  pcf.pinMode(1, INPUT_PULLUP);
  pcf.pinMode(2, INPUT_PULLUP);
  pcf.pinMode(3, INPUT_PULLUP);
  pcf.pinMode(4, INPUT_PULLUP);
  pcf.pinMode(5, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

bool _readButton(int channel)
{
  uint8_t val = pcf.digitalRead(channel);
  return val;
  delay(10);
}

bool touchUp(int button) {
  if (!_readButton(button)) {
    while (!_readButton(button)) {}
     return true;
  }
  return false;
}


bool touchDown(int button , int del) {
  bool val ;
  if (!_readButton(button)){
    while (_readButton(button))
     val = true;
     delay(del);
     del -=5;
  }else val = false;
  
  return val ;
}
