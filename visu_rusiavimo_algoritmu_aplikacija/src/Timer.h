#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>
#include <vector>

class Timer {
public:
  typedef std::chrono::high_resolution_clock Clock;
  Timer();
  void init(std::string name, int skip);
  Timer(std::string name, int skip);
  void Start();
  void Stop();
  void GetDetailTimes();

private:
  Clock::time_point start;
  std::vector<double> times;
  std::string name;
  int skip;
  int currentStep;
};

#endif // TIMER_H
