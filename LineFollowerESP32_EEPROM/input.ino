// ===========================================================================
// Implementasi input non-blocking.
// ===========================================================================

static bool          _raw[NBTN];
static bool          _stable[NBTN];
static unsigned long _lastChange[NBTN];
static unsigned long _pressStart[NBTN];
static unsigned long _lastRepeat[NBTN];

void initInput() {
  Wire.begin();
  pcf.begin(PCF8574_ADDR, &Wire);
  for (uint8_t i = 0; i < NBTN; i++) {
    pcf.pinMode(pcfPin[i], INPUT_PULLUP);
    _raw[i] = _stable[i] = false;
    _lastChange[i] = _pressStart[i] = _lastRepeat[i] = 0;
  }
  pinMode(LED_PIN, OUTPUT);
}

// Dipanggil tepat satu kali di awal loop() (dan tiap iterasi loop balapan).
void inputUpdate() {
  unsigned long now = millis();
  for (uint8_t i = 0; i < NBTN; i++) {
    kPressed[i] = kReleased[i] = kRepeat[i] = false;

    bool raw = !pcf.digitalRead(pcfPin[i]);   // aktif-low: ditekan = true
    if (raw != _raw[i]) { _raw[i] = raw; _lastChange[i] = now; }

    if ((now - _lastChange[i]) > DEBOUNCE_MS && raw != _stable[i]) {
      _stable[i] = raw;
      if (raw) {                 // baru ditekan
        kPressed[i] = true;
        kRepeat[i]  = true;      // satu kali aksi langsung saat tap
        _pressStart[i] = now;
        _lastRepeat[i] = now;
      } else {
        kReleased[i] = true;
      }
    }

    kDown[i] = _stable[i];

    // auto-repeat saat ditahan (untuk increment/decrement nilai)
    if (_stable[i] && !kPressed[i]) {
      if ((now - _pressStart[i]) > REPEAT_DELAY && (now - _lastRepeat[i]) > REPEAT_RATE) {
        kRepeat[i] = true;
        _lastRepeat[i] = now;
      }
    }
  }
}

bool btnPressed (uint8_t b) { return kPressed[b]; }
bool btnReleased(uint8_t b) { return kReleased[b]; }
bool btnRepeat  (uint8_t b) { return kRepeat[b]; }
bool btnDown    (uint8_t b) { return kDown[b]; }
