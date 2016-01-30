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
    g_LuaRuntime->sl->mm_api->ConPrintf("%s\n", lua_tostring(L, 1));
  }
  return 0;
}

void LuaRuntime::register_std_lib() {
  luaopen_Logger(L, this->sl);
  lua_register(L, "print", LuaPrint);
}
