#ifndef _INCLUDE_LUARUNTIME
#define _INCLUDE_LUARUNTIME

#include "lua.hpp"
#include <ISmmPlugin.h>
#include "sourcelua.hpp"
#include <functional>

class LuaRuntime : public SourceLuaBase {
public:
  LuaRuntime();
  void Init();
  void LoadAddons();
  void LoadAddon(const char *addonDir);
  META_RES FireClientCommand(int client, const CCommand args);
  lua_State *L;

public:
  void OnPluginStart();
private:
  void register_std_lib();
  void lua_chroot(const char *root, std::function<void(void)>);
  char *basePath;
};

int lua_traceback(lua_State *L);
inline int lua_docall(lua_State *L, int nargs, int ret);

extern LuaRuntime g_LuaRuntime;

#endif //_INCLUDE_LUARUNTIME
