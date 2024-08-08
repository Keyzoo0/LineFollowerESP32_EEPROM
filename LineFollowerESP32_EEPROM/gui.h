byte modeMPU = 1 ;
byte modeWIFI= 1 ;
byte modeLF = 1 ;
byte modeENC = 1 ;
byte menuSet = 1 ;
byte countMenu = 1;
byte menuHome = 0;
byte halaman = 0;
bool homeS = true;
byte menuIdx = 0;
byte selectSet = 0;
byte halIdx = 0;
byte menuCount = 0;
byte IdIdx;
byte profilePid;

const char* set[] = {"OFF" , "ON"};
const char* mode_lf[] = {"TRANSPORTER" , "LINE TRACER"};
const char* set_wifi[] = {"Disconnect" , "Connected"};
