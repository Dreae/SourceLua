#ifndef _INCLUDE_LUARUNTIME_LUALIBS_SERVER
#define _INCLUDE_LUARUNTIME_LUALIBS_SERVER

#include "sourcelua.hpp"
#include "lua.hpp"

int lua_GetClientName(lua_State *L);
void lua_register_Server(lua_State *L);

#endif // _INCLUDE_LUARUNTIME_LUALIBS_SERVER
