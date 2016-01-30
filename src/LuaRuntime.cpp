#include "LuaRuntime.hpp"
#include "sourcelua.hpp"

LuaRuntime::LuaRuntime() {
  L = NULL;
  this->ismm = NULL;
}

LuaRuntime::LuaRuntime(ISmmAPI *ismm) {
  L = NULL;
  this->ismm = ismm;
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
  g_LuaRuntime.ismm->ConPrint("LuaPrint");
}

void LuaRuntime::register_std_lib() {
  lua_newtable(L);
  lua_pushstring(L, SOURCELUA_VERSION);
  lua_setfield(L, -2, "version");
  lua_setglobal(L, "SourceLua");

  lua_register(L, "print", LuaPrint);
}
