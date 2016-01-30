#ifndef _INCLUDE_LUARUNTIME_LOGGER
#define _INCLUDE_LUARUNTIME_LOGGER

#include "sourcelua.hpp"

class Logger {
public:
  Logger(SourceLua *sl);
  void info(const char *msg);
  void warn(const char *msg);
  void error(const char* msg);
private:
  SourceLua *sl;
};

#endif // _INCLUDE_LUARUNTIME_LOGGER
