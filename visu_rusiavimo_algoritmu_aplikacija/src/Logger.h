#ifndef LOGGER_H
#define LOGGER_H
#include "thirdParty/spdlog/spdlog.h"

class Logger {
private:
  /* Here will be the instance stored. */
  static Logger *instance;

  /* Private constructor to prevent instancing. */
  Logger();

public:
  /* Static access method. */
  static Logger *getInstance();
  std::shared_ptr<spdlog::logger> LoggerConsole =
      spdlog::stdout_color_mt("console");

  std::shared_ptr<spdlog::logger> LoggerTimers =
      spdlog::basic_logger_mt("timers_logger", "logs/timers.log", true);
  std::shared_ptr<spdlog::logger> LoggerBuild =
      spdlog::basic_logger_mt("build_logger", "logs/build.log", true);
  std::shared_ptr<spdlog::logger> LoggerInfo =
      spdlog::basic_logger_mt("info_logger", "logs/info.log", true);
};

#endif // LOGGER_H
