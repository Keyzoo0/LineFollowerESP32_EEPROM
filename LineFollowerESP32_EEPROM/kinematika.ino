// #include "kinematika.h"

void IRAM_ATTR TimerPlay(){ // timer for calculate play
  portENTER_CRITICAL_ISR(&timerMux);
  timeIdxTA++;
  timeIdxTB++;
  timeIdxPlay++;
  timeCountSpeed++;
  portEXIT_CRITICAL_ISR(&timerMux);
}



void readCounter(byte count) {
  int16_t speedPlayR, speedPlayL = 0;
  int16_t speedL, speedR;

  switch (count) { // stop
    case 0:
      stopMotor();
      break;

    case 1: // maju
      speedPlayL = spdL[plan][countIdxPlay];
      speedL = speedPlayL / 4;
      lastTimeIdxPlay = timeIdxPlay;
      while (1) {
        if (speedL < speedPlayL) {
          speedL += 2;
          if (speedL > speedPlayL) {
            speedL = speedPlayL;
          }
        }
        speedOne(speedL);
        if (timeIdxPlay - lastTimeIdxPlay >= idelay[plan][countIdxPlay]) break;
        if(countCP != 0){
          if (timeIdxPlay - lastTimeIdxPlay >= iDelayCheckpoint[plan][countCP]) break;
        }
        
      }
      lastTimeIdxPlay = 0;
      break;

    case 2: // kiri
      pwmMotor(spdL[plan][countIdxPlay] * -1, spdR[plan][countIdxPlay]);
      delay(idelay[plan][countIdxPlay]);
      break;

    case 3: // kanan
      pwmMotor(spdL[plan][countIdxPlay], spdR[plan][countIdxPlay] * -1);
      delay(idelay[plan][countIdxPlay]);
      break;

    case 4: // mundur
      speedPlayL = spdL[plan][countIdxPlay];
      speedL = speedPlayL / 4;
      timeIdxPlay = 0;
      while (1) {
        if (speedL < speedPlayL) {
          speedL += 2;
          if (speedL > speedPlayL) {
            speedL = speedPlayL;
          }
        }
        speedOne(speedL * -1);
        if (timeIdxPlay - lastTimeIdxPlay >= idelay[plan][countIdxPlay]) break;
      }
      lastTimeIdxPlay = 0;
      break;

    case 7: // TLeft
    while(1){
    pwmMotor(-200, 200);
    delay(idelay[plan][countIdxPlay]);
    if(readSensor() & 0b00000011000000){break;}
    else if(readSensor() & 0b11111100111111){break;}
    } // end while bracket
    break;

    case 8: // TRight
    while(1){
    pwmMotor(200, -200);
    delay(idelay[plan][countIdxPlay]);
    if(readSensor() & 0b00000011000000){break;}
    else if(readSensor() & 0b11111100111111){break;}
    } // end while bracket
    break;
  }
}
