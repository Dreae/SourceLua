#include "luaruntime/lualibs/Server.hpp"

int lua_GetClientName(lua_State *L) {
  IPlayerInfo *info = g_iPlayerInfo->GetPlayerInfo(g_Engine->PEntityOfEntIndex(lua_tointeger(L, 1)));
  lua_pushstring(L, info->GetName());
  return 1;
}

int lua_register_Server(lua_State *L) {
  lua_getglobal(L, "SourceLua");
  lua_newtable(L);
  lua_pushcfunction(L, lua_GetClientName);
  lua_setfield(L, -2, "GetClientName");
  lua_setfield(L, -2, "Server");
  lua_remove(L, -2);
}
