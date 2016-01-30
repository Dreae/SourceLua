#include "luaruntime/LuaRuntime.hpp"
#include "luaruntime/lua_cclass/LuaLogger.hpp"

LuaRuntime::LuaRuntime(SourceLua *sl) {
  L = NULL;
  this->sl = sl;
}

void LuaRuntime::Init() {
  L = luaL_newstate();
  lua_gc(L, LUA_GCSTOP, 0);
  luaL_openlibs(L);
  lua_gc(L, LUA_GCRESTART, 0);

  luaJIT_setmode(L, 0, LUAJIT_MODE_ENGINE | LUAJIT_MODE_ON);
  this->register_std_lib();
}

int LuaPrint(lua_State *L) {
  if(lua_gettop(L)) {
    if(!lua_isstring(L, 1)) {
      lua_getglobal(L, "tostring");
      lua_pushvalue(L, 1);
      lua_call(L, 1, 1);
    }
    g_SMAPI->ConPrintf("%s\n", lua_tostring(L, -1));
  }
  return 0;
}

void updateLuaPath(lua_State *L) {
  lua_getglobal(L, "package");
  lua_getfield(L, -1, "path");

  const char *oldPath = lua_tostring(L, -1);
  const char *gameDir = g_SMAPI->GetBaseDir();
  size_t maxlen = strlen(gameDir) + 64;
  char *luaPath = new char[maxlen];

  g_SMAPI->PathFormat(luaPath, maxlen, "%s/addons/sourcelua/lua/?.lua", gameDir);
  maxlen += strlen(oldPath) + 1;
  char *finalPath = new char[maxlen];

  g_SMAPI->Format(finalPath, maxlen, "%s;%s", oldPath, luaPath);
  lua_getglobal(L, "package");
  lua_pushstring(L, finalPath);
  lua_setfield(L, -2, "path");
  lua_remove(L, -1);
}

void LuaRuntime::register_std_lib() {
  updateLuaPath(L);

  lua_register(L, "print", LuaPrint);

  luaopen_Logger(L, this->sl);

  lua_getglobal(L, "require");
  lua_pushstring(L, "sourcelua");
  lua_call(L, 1, 1);
  lua_setglobal(L, "SourceLua");
}
