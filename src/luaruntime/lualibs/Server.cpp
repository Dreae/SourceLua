#include "luaruntime/lualibs/Server.hpp"
#include "convar.h"
#include "Console.hpp"


int lua_GetClientName(lua_State *L) {
  IPlayerInfo *info = g_iPlayerInfo->GetPlayerInfo(g_Engine->PEntityOfEntIndex(lua_tointeger(L, 1)));
  lua_pushstring(L, info->GetName());
  return 1;
}

CommandCallback lua_pushConCmd(int pluginId) {
  return [pluginId](const CCommand &cmd) -> META_RES {
    CONMSG("Plugin %d got lua registered command %s\n", pluginId, cmd.Arg(0));
    return MRES_SUPERCEDE;
  }; // #TODO: Forward command to lua local addon manager
}

int lua_RegServerCmd(lua_State *L) {
  const char *name = lua_tostring(L, 1);
  const char *help = lua_tostring(L, 2);
  int flags = lua_tointeger(L, 3);
  g_Console.HookOrAddConCommand(name, lua_pushConCmd(0), help, flags);
  return 0;
}

void lua_register_Server(lua_State *L) {
  lua_getglobal(L, "SourceLua");
  lua_newtable(L);
  lua_pushcfunction(L, lua_GetClientName);
  lua_setfield(L, -2, "GetClientName");
  lua_pushcfunction(L, lua_RegServerCmd);
  lua_setfield(L, -2, "RegServerCmd");
  lua_setfield(L, -2, "Server");
  lua_remove(L, -2);
}
