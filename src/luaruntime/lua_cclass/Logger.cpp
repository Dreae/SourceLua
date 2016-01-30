#include "luaruntime/lua_cclass/Logger.hpp"

Logger::Logger(SourceLua *sl) {
  this->sl = sl;
}

void Logger::info(const char *msg) {
  size_t maxlen = sizeof(char) * (strlen(msg) + 16);
  char *buffer = (char *)malloc(maxlen);

  this->sl->mm_api->Format(buffer, maxlen, "[INFO] %s", msg);
  this->sl->mm_api->LogMsg(this->sl, (const char*)buffer);
}

void Logger::warn(const char *msg) {
  size_t maxlen = sizeof(char) * (strlen(msg) + 16);
  char *buffer = (char *)malloc(maxlen);

  this->sl->mm_api->Format(buffer, maxlen, "[WARN] %s", msg);
  this->sl->mm_api->LogMsg(this->sl, (const char*)buffer);
}

void Logger::error(const char *msg) {
  size_t maxlen = sizeof(char) * (strlen(msg) + 16);
  char *buffer = (char *)malloc(maxlen);

  this->sl->mm_api->Format(buffer, maxlen, "[ERROR] %s", msg);
  this->sl->mm_api->LogMsg(this->sl, (const char*)buffer);
}
