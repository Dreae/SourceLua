#include "lua.hpp"
#include <ISmmPlugin.h>

class LuaRuntime {
public:
  LuaRuntime();
  LuaRuntime(ISmmAPI *ismm);
  void Init();
  lua_State *L;
  ISmmAPI *ismm;
private:
  void register_std_lib();
};

extern LuaRuntime g_LuaRuntime;
