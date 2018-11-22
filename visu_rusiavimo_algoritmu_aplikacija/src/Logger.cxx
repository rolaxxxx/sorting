#include "Logger.h"

Logger *Logger::instance = 0;

Logger *Logger::getInstance() {
  if (instance == 0) {
    instance = new Logger();
  }

  return instance;
}

Logger::Logger() { spdlog::set_pattern("%v"); }
