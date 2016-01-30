#ifndef _INCLUDE_LUARUNTIME
#define _INCLUDE_LUARUNTIME

#include "lua.hpp"
#include <ISmmPlugin.h>
#include "sourcelua.hpp"

class LuaRuntime {
public:
  LuaRuntime(SourceLua *sl);
  void Init();
  lua_State *L;
  SourceLua *sl;
private:
  void register_std_lib();
};

extern LuaRuntime *g_LuaRuntime;

#endif //_INCLUDE_LUARUNTIME
