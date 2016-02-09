#ifndef _INCLUDE_LUARUNTIME_LUALIBS_CURL
#define _INCLUDE_LUARUNTIME_LUALIBS_CURL

#include "curl/curl.h"
#include "lua.hpp"
#include "sourcelua.hpp"

typedef struct {
  char *data;
  size_t bufferSize;
  size_t dataSize;
  int callbackRef;
} CurlReq;

class LuaCurl : public SourceLuaBase {
public:
  LuaCurl() { };
  void Get(const char *url, int callbackRef);

public:
  void OnPluginStart();
  void OnGameFrame(bool simulating);

private:
  CURLM *mCurlHandle;
  int running_handles;
};

void lua_register_Curl(lua_State *L);

#endif //_INCLUDE_LUARUNTIME_LUALIBS_CURL
