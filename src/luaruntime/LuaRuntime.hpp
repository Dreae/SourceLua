#ifndef _INCLUDE_LUARUNTIME
#define _INCLUDE_LUARUNTIME

#include "lua.hpp"
#include <ISmmPlugin.h>
#include "sourcelua.hpp"
#include <functional>

class LuaRuntime {
public:
  LuaRuntime(SourceLua *sl);
  void Init();
  void LoadAddons();
  void LoadAddon(const char *addonDir);
  void FireClientCommand(int client, const CCommand args);
  lua_State *L;
  SourceLua *sl;
private:
  void register_std_lib();
  void lua_chroot(const char *root, std::function<void(void)>);
  char *basePath;
};

extern LuaRuntime *g_LuaRuntime;

#endif //_INCLUDE_LUARUNTIME
