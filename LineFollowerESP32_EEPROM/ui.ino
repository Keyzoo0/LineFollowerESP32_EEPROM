// ===========================================================================
// Dispatcher UI: enter/push/pop + handle/render per layar.
// ===========================================================================

void enterScreen(Screen s) {
  uiCur = s;
  switch (s) {                       // reset state lokal saat masuk layar
    case SCR_HOME:        stHome.sel = 0; break;
    case SCR_MENU:        stMenu.sel = 0; break;
    case SCR_SETTINGS:    stSettings.sel = 0; break;
    case SCR_THROTTLE:    stThrottle.sel = 0; break;
    case SCR_SETDEFAULT:  stSetDef.step = 0; stSetDef.yes = false; break;
    case SCR_SETINDEX:    stIdx.curIdx = 0; stIdx.row = 0; break;
    case SCR_ADDREMOVE:   stAddRem.curIdx = stIdx.curIdx; break;
    case SCR_CHECKPOINT:  stCp.sel = 0; stCp.cp = countCP; break;
    case SCR_CALIB:       stCalib.sel = 0; break;
    case SCR_CALIB_AUTO:  stCalAuto.step = 0; stCalAuto.sens = 0; break;
    case SCR_CALIB_MANUAL:stCalMan.menu = 0; stCalMan.sel = 0; break;
    case SCR_TUNEPID:     stTune.sel = 0; stTune.preset = 0; stTune.flmode = 0; break;
    case SCR_TESTMOTOR:   stTest.col = 0; stTest.row = 0; stTest.spR = stTest.spL = 0;
                          stTest.dirR = stTest.dirL = 0; initEncoder(true); break;
    case SCR_COPYMIRROR:  stCM.step = 0; stCM.mirror = false; stCM.x1 = 0; stCM.x2 = 0; break;
    case SCR_RESETPLAN:   stReset.step = 0; stReset.yes = false; break;
    default: break;
  }
  oledClear();
}

void setScreen(Screen s) { uiSp = 0; enterScreen(s); }

void pushScreen(Screen s) {
  if (uiSp < UI_DEPTH) uiStack[uiSp++] = uiCur;
  enterScreen(s);
}

void popScreen() {
  if (uiSp > 0) enterScreen(uiStack[--uiSp]);
  else          enterScreen(SCR_HOME);
}

void uiHandle() {
  switch (uiCur) {
    case SCR_HOME:         handleHome();        break;
    case SCR_MENU:         handleMenu();        break;
    case SCR_SETTINGS:     handleSettings();    break;
    case SCR_THROTTLE:     handleThrottle();    break;
    case SCR_SETDEFAULT:   handleSetDefault();  break;
    case SCR_SETINDEX:     handleSetIndex();    break;
    case SCR_ADDREMOVE:    handleAddRemove();   break;
    case SCR_CHECKPOINT:   handleCheckpoint();  break;
    case SCR_CALIB:        handleCalib();       break;
    case SCR_CALIB_AUTO:   handleCalibAuto();   break;
    case SCR_CALIB_MANUAL: handleCalibManual(); break;
    case SCR_TUNEPID:      handleTunePid();     break;
    case SCR_TESTMOTOR:    handleTestMotor();   break;
    case SCR_COPYMIRROR:   handleCopyMirror();  break;
    case SCR_RESETPLAN:    handleResetPlan();   break;
    case SCR_RACE_RESULT:  handleRaceResult();  break;
  }
}

void uiRender() {
  lcd.clearDisplay();
  switch (uiCur) {
    case SCR_HOME:         renderHome();        break;
    case SCR_MENU:         renderMenu();        break;
    case SCR_SETTINGS:     renderSettings();    break;
    case SCR_THROTTLE:     renderThrottle();    break;
    case SCR_SETDEFAULT:   renderSetDefault();  break;
    case SCR_SETINDEX:     renderSetIndex();    break;
    case SCR_ADDREMOVE:    renderAddRemove();   break;
    case SCR_CHECKPOINT:   renderCheckpoint();  break;
    case SCR_CALIB:        renderCalib();       break;
    case SCR_CALIB_AUTO:   renderCalibAuto();   break;
    case SCR_CALIB_MANUAL: renderCalibManual(); break;
    case SCR_TUNEPID:      renderTunePid();     break;
    case SCR_TESTMOTOR:    renderTestMotor();   break;
    case SCR_COPYMIRROR:   renderCopyMirror();  break;
    case SCR_RESETPLAN:    renderResetPlan();   break;
    case SCR_RACE_RESULT:  renderRaceResult();  break;
  }
  lcd.display();
}
