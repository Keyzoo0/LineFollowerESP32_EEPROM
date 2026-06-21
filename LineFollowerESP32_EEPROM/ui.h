#ifndef UI_H
#define UI_H

// ===========================================================================
// UI LAYER — state machine layar + stack (menggantikan semua while(1) blocking).
// Tiap layar punya state LOKAL sendiri (struct di bawah) -> tidak ada lagi
// variabel global yang dipakai bersama antar menu (sumber konflik lama hilang).
// ===========================================================================

enum Screen {
  SCR_HOME, SCR_MENU, SCR_SETTINGS, SCR_THROTTLE, SCR_SETDEFAULT,
  SCR_SETINDEX, SCR_ADDREMOVE, SCR_CHECKPOINT,
  SCR_CALIB, SCR_CALIB_AUTO, SCR_CALIB_MANUAL,
  SCR_TUNEPID, SCR_TESTMOTOR, SCR_COPYMIRROR, SCR_RESETPLAN,
  SCR_RACE_RESULT
};

#define UI_DEPTH 8
Screen uiStack[UI_DEPTH];
int    uiSp  = 0;
Screen uiCur = SCR_HOME;

//============================ state per-layar ============================
struct { int8_t sel; bool race; }                                  stHome;
struct { int8_t sel; }                                             stMenu;
struct { int8_t sel; }                                             stSettings;
struct { int8_t sel; }                                             stThrottle;
struct { int8_t step; bool yes; }                                  stSetDef;
struct { int curIdx; int8_t row; }                                 stIdx;
struct { int curIdx; }                                             stAddRem;
struct { int8_t sel; int8_t cp; }                                  stCp;
struct { int8_t sel; }                                             stCalib;
struct { int8_t step; int8_t sens; }                               stCalAuto;
struct { int8_t menu; int8_t sel; }                                stCalMan;
struct { int8_t sel; int8_t preset; int8_t flmode; }              stTune;
struct { int8_t col; int8_t row; int spR; int spL; int8_t dirR; int8_t dirL; } stTest;
struct { int8_t step; bool mirror; byte x1; byte x2; }             stCM;
struct { int8_t step; bool yes; byte target; }                     stReset;
struct { int stopIdx; double elapsed; }                            stResult;

//============================== prototipe ===============================
void enterScreen(Screen s);
void setScreen(Screen s);
void pushScreen(Screen s);
void popScreen();
void uiHandle();
void uiRender();

void handleHome();       void renderHome();
void handleMenu();       void renderMenu();
void handleSettings();   void renderSettings();
void handleThrottle();   void renderThrottle();
void handleSetDefault(); void renderSetDefault();
void handleSetIndex();   void renderSetIndex();
void handleAddRemove();  void renderAddRemove();
void handleCheckpoint(); void renderCheckpoint();
void handleCalib();      void renderCalib();
void handleCalibAuto();  void renderCalibAuto();
void handleCalibManual();void renderCalibManual();
void handleTunePid();    void renderTunePid();
void handleTestMotor();  void renderTestMotor();
void handleCopyMirror(); void renderCopyMirror();
void handleResetPlan();  void renderResetPlan();
void handleRaceResult(); void renderRaceResult();

void runRace();          // loop balapan real-time (lihat race.ino)

#endif // UI_H
