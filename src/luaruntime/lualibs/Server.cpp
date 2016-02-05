#include "luaruntime/lualibs/Server.hpp"
#include "luaruntime/LuaRuntime.hpp"
#include "convar.h"
#include "Console.hpp"


int lua_GetClientName(lua_State *L) {
  IPlayerInfo *info = g_iPlayerInfo->GetPlayerInfo(g_Engine->PEntityOfEntIndex(lua_tointeger(L, 1)));
  lua_pushstring(L, info->GetName());
  return 1;
}

CommandCallback lua_pushConCmd(lua_State *L, int callbackRef) {
  return [L, callbackRef](const CCommand &cmd) -> META_RES {
    lua_pushcfunction(L, lua_traceback);
    lua_rawgeti(L, LUA_REGISTRYINDEX, callbackRef);

    int argc = cmd.ArgC();
    lua_newtable(L);
    for(int c = 0; c < argc; c++) {
      lua_pushstring(L, cmd.Arg(c));
      lua_rawseti(L, -2, c + 1);
    }

    if(lua_pcall(L, 1, 1, -3)) {
      META_LOG(g_PLAPI, "Error in addon: %s", lua_tostring(L, -1));
    }
    return (META_RES)lua_tointeger(L, -1);
  };
}

int lua_RegServerCmd(lua_State *L) {
  const char *name = lua_tostring(L, 1);

  lua_pushvalue(L, 2); // Move ref to top of stack
  int ref = luaL_ref(L, LUA_REGISTRYINDEX); // Save it in the registry

  const char *help = lua_tostring(L, 3);
  int flags = lua_tointeger(L, 4);
  g_Console.HookOrAddConCommand(name, lua_pushConCmd(L, ref), help, flags);
  return 0;
}

void lua_register_Server(lua_State *L) {
  lua_getglobal(L, "SourceLua");
  lua_getglobal(L, "require");
  lua_pushstring(L, "server");
  lua_call(L, 1, 1);
  lua_pushcfunction(L, lua_GetClientName);
  lua_setfield(L, -2, "GetClientName");
  lua_pushcfunction(L, lua_RegServerCmd);
  lua_setfield(L, -2, "RegServerCmd");
  lua_setfield(L, -2, "Server");
  lua_remove(L, -2);
}
