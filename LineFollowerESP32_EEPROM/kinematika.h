

//============race===============
int dataSensor;
int16_t maxS;
byte countIdxPlay;
uint16_t timerSpeedA;
uint16_t timerSpeedB;
uint16_t TA;
uint16_t TB;
int16_t sensLogPlay;
bool clrLinePlay;
bool playAction = false;
long lastTimA;
long lastTimB;

volatile long timeIdxPlay;
unsigned long lastTimeIdxPlay;
volatile long timeIdxTA;
unsigned long lastTimeIdxTA;
volatile long timeIdxTB;
unsigned long lastTimeIdxTB;
volatile long timeCountSpeed;
unsigned long lastCountSpeed;

