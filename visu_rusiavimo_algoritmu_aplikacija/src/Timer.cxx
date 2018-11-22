#include "Timer.h"
#include "Logger.h"
#include <ctime>
#include <iostream>
#include <numeric>
#include <ratio>
#include <sstream>

Timer::Timer(std::string name, int skip) { this->init(name, skip); }

Timer::Timer() {}

void Timer::init(std::string name, int skip) {
  this->name = name;
  this->skip = skip;
  this->currentStep = 0;
}

void Timer::Start() { start = Clock::now(); }

void Timer::Stop() {
  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(Clock::now() -
                                                                start);
  times.push_back(time_span.count());
  currentStep++;
  if ((currentStep % skip) == 0) {
    GetDetailTimes();
    currentStep = 0;
  }
}

void Timer::GetDetailTimes() {
  double totalTime = 0;
  // double max = 0;
  // double min = 0;
  double average = 0;
  if (times.size() > 0) {
    totalTime = std::accumulate(times.begin(), times.end(), totalTime);
    // max = *std::max_element(times.begin(), times.end());
    // min = *std::min_element(times.begin(), times.end());
    average = totalTime / times.size();
  }

  times.resize(0, 0);
  times.reserve(skip);
  Logger::getInstance()->LoggerConsole->info("{} Total time {} Average {}",this->name,totalTime,average);

}
