#include "luaruntime/LuaRuntime.hpp"
#include "luaruntime/lualibs/Server.hpp"
#include "luaruntime/lualibs/Curl.hpp"

LuaRuntime g_LuaRuntime;

LuaRuntime::LuaRuntime() {
  L = luaL_newstate();
  this->basePath = new char[PATH_MAX];
}

void LuaRuntime::OnPluginStart() {
  const char *gameDir = g_SMAPI->GetBaseDir();
  g_SMAPI->PathFormat(this->basePath, PATH_MAX, "%s/addons/sourcelua/lua/?.lua", gameDir);

  lua_gc(L, LUA_GCSTOP, 0);
  luaL_openlibs(L);
  lua_gc(L, LUA_GCRESTART, 0);

  luaJIT_setmode(L, 0, LUAJIT_MODE_ENGINE | LUAJIT_MODE_ON);

  // Update lua require path
  lua_getglobal(L, "package");
  lua_pushstring(L, this->basePath);
  lua_setfield(L, -2, "path");
  lua_remove(L, -1);

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

int lua_traceback (lua_State *L) {
  if (!lua_isstring(L, 1))  /* 'message' not a string? */
    return 1;  /* keep it intact */
  lua_getfield(L, LUA_GLOBALSINDEX, "debug");
  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return 1;
  }
  lua_getfield(L, -1, "traceback");
  if (!lua_isfunction(L, -1)) {
    lua_pop(L, 2);
    return 1;
  }
  lua_pushvalue(L, 1);  /* pass error message */
  lua_pushinteger(L, 2);  /* skip this function and traceback */
  lua_call(L, 2, 1);  /* call debug.traceback */
  return 1;
}

void LuaRuntime::register_std_lib() {
  lua_register(L, "print", LuaPrint);

  lua_getglobal(L, "require");
  lua_pushstring(L, "sourcelua");
  lua_call(L, 1, 1);
  lua_setglobal(L, "SourceLua");

  //Save gameDir
  const char* gameDir = g_SMAPI->GetBaseDir();
  lua_getglobal(L, "SourceLua");
  lua_pushstring(L, gameDir);
  lua_setfield(L, -2, "BaseDir");

  char slDir[PATH_MAX];
  strcpy(slDir, g_plPath);
  slDir[strlen(slDir) - 4] = 0; // Chop of /bin #FIXME: Find better way?
  lua_pushstring(L, slDir);
  lua_setfield(L, -2, "SourceLuaDir");

  lua_register_Server(L);
  lua_register_Curl(L);
}

void LuaRuntime::LoadAddons() {
  FileFindHandle_t findHandle;
  const char *filename = g_iFileSystem->FindFirstEx("addons/sourcelua/addons/*.*", "MOD", &findHandle);
  while(filename) {
    char addonDir[PATH_MAX];
    char indexFile[PATH_MAX];
    g_SMAPI->PathFormat(addonDir, PATH_MAX, "addons/sourcelua/addons/%s", filename);
    g_SMAPI->PathFormat(indexFile, PATH_MAX, "%s/index.lua", addonDir);

    if(g_iFileSystem->FileExists(indexFile)) {
      this->LoadAddon(addonDir);
    }

    filename = g_iFileSystem->FindNext(findHandle);
  }
}

void LuaRuntime::LoadAddon(const char *addonDir) {
  this->lua_chroot(addonDir, [this]() -> void { // #TODO: Create addon context for per-addon managers
    lua_pushcfunction(this->L, lua_traceback);
    lua_getglobal(this->L, "require");
    lua_pushstring(this->L, "index");
    if(lua_pcall(this->L, 1, 1, -3)) {
      META_LOG(g_PLAPI, "Error loading addon: %s", lua_tostring(this->L, -1));
    }
  });
}

void LuaRuntime::lua_chroot(const char *addonDir, std::function<void(void)> f) {
  char path[PATH_MAX * 2];
  g_SMAPI->PathFormat(path, PATH_MAX * 2, "%s;%s/%s/?.lua", this->basePath, g_SMAPI->GetBaseDir(), addonDir);
  lua_getglobal(this->L, "package");
  lua_pushstring(this->L, path);
  lua_setfield(this->L, -2, "path");
  lua_remove(this->L, -1);

  f();

  lua_getglobal(this->L, "package");
  lua_pushstring(this->L, this->basePath);
  lua_setfield(this->L, -2, "path");
  lua_remove(this->L, -1);
}

META_RES LuaRuntime::FireClientCommand(int client, const CCommand args) {
  lua_getglobal(this->L, "SourceLua");
  lua_getfield(this->L, -1, "Events");
  lua_remove(this->L, -2);

  lua_getfield(this->L, -1, "FireClientCommand");
  lua_remove(this->L, -2);

  lua_pushinteger(this->L, client);
  lua_createtable(this->L, args.ArgC(), 0);
  for(int i = 1; i <= args.ArgC(); i++) {
    lua_pushstring(this->L, args.Arg(i - 1));
    lua_rawseti(this->L, -2, i);
  }
  if(lua_pcall(this->L, 2, 1, 0)) {
    META_LOG(g_PLAPI, "Error firing client command: %s", lua_tostring(this->L, -1));
    return MRES_IGNORED;
  }
  return (META_RES)lua_tointeger(this->L, -1);
}
