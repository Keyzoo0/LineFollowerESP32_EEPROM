#ifndef TIMER_H
#define TIMER_H

// Stopwatch ringan berbasis millis() — menggantikan library StopWatch eksternal.
struct SimpleStopWatch {
  unsigned long _start = 0, _acc = 0;
  bool _run = false;
  void reset() { _acc = 0; _run = false; }
  void start() { if (!_run) { _start = millis(); _run = true; } }
  void stop()  { if (_run)  { _acc += millis() - _start; _run = false; } }
  unsigned long elapsed() { return _run ? _acc + (millis() - _start) : _acc; }
};

SimpleStopWatch sw_millis;

#endif // TIMER_H
