#ifndef _INCLUDE_LUARUNTIME_LUALIBS_CURL
#define _INCLUDE_LUARUNTIME_LUALIBS_CURL

#include "curl/curl.h"
#include "lua.hpp"

void lua_register_Curl(lua_State *L);

#endif //_INCLUDE_LUARUNTIME_LUALIBS_CURL
