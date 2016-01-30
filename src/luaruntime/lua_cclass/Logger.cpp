#include "luaruntime/lua_cclass/Logger.hpp"

Logger::Logger(SourceLua *sl) {
  this->sl = sl;
}

void Logger::info(const char *msg) {
  this->sl->mm_api->LogMsg(this->sl, "[INFO] %s", msg);
}

void Logger::warn(const char *msg) {
  this->sl->mm_api->LogMsg(this->sl, "[WARN] %s", msg);
}

void Logger::error(const char *msg) {
  this->sl->mm_api->LogMsg(this->sl, "[ERROR] %s", msg);
}
