

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

unsigned int scann;
byte slct;
byte countCp;
byte start = 0;
byte count;
byte stopCount = 1;
byte counting;
bool mode = true;
bool protec = false;
bool invers;
byte spdStart;
byte vSpeed;
int timeTrig;


volatile long timeIdxPlay;
unsigned long lastTimeIdxPlay;
volatile long timeIdxTA;
unsigned long lastTimeIdxTA;
volatile long timeIdxTB;
unsigned long lastTimeIdxTB;
volatile long timeCountSpeed;
unsigned long lastCountSpeed;

