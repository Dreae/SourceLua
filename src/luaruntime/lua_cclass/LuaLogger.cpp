#include "lua.hpp"
#include "luaruntime/luawrapper.hpp"
#include "luaruntime/lua_cclass/Logger.hpp"

int Logger_info(lua_State *L) {
  Logger *logger = luaW_check<Logger>(L, 1);
  logger->info(lua_tostring(L, 2));
  return 0;
}

int Logger_warn(lua_State *L) {
  Logger *logger = luaW_check<Logger>(L, 1);
  logger->info(lua_tostring(L, 2));
  return 0;
}

int Logger_error(lua_State *L) {
  Logger *logger = luaW_check<Logger>(L, 1);
  logger->info(lua_tostring(L, 2));
  return 0;
}

static luaL_Reg Logger_metatable[] = {
  { "info", Logger_info },
  { "warn", Logger_warn },
  { "error", Logger_error },
  {NULL, NULL}
};

int luaopen_Logger(lua_State *L, SourceLua *sl) {
  luaW_register<Logger>(L, "MMAPILogger", NULL, Logger_metatable, NULL);
  Logger *logger = new Logger(sl);
  luaW_push<Logger>(L, logger);
  lua_setglobal(L, "MetaLogger");
  return 1;
}
