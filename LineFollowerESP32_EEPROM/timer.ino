
void initTimer(){
  
  Timer0_Encoder = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Encoder, &TimerEncoder, true);
  timerAlarmWrite(Timer0_Encoder, 10000, true);
  timerAlarmEnable(Timer0_Encoder);

  Timer1_Play = timerBegin(1, 80, true);
  timerAttachInterrupt(Timer1_Play, &TimerPlay, true);
  timerAlarmWrite(Timer1_Play, 10000, true);
  timerAlarmEnable(Timer1_Play);

  Timer2_PID = timerBegin(2, 80, true);
  timerAttachInterrupt(Timer2_PID, &TimerPID, true);
  timerAlarmWrite(Timer2_PID, 1000, true);
  timerAlarmEnable(Timer2_PID);
  
}