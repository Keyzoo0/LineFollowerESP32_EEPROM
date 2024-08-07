// #include "kinematika.h"

void IRAM_ATTR TimerPlay(){ // timer for calculate play
  portENTER_CRITICAL_ISR(&timerMux);
  timeIdxTA++;
  timeIdxTB++;
  timeIdxPlay++;
  timeCountSpeed++;
  portEXIT_CRITICAL_ISR(&timerMux);
}