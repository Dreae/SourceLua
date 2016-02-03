#ifndef _INCLUDE_CONSOLE
#define _INCLUDE_CONSOLE
#include <ISmmPlugin.h>
#include "sourcelua.hpp"

class SourceLuaConsole : public SourceLuaBase {
public:
  SourceLuaConsole() { };
  META_RES DispatchClientCmd(edict_t *client, const CCommand &command);
  void RegConCommand(const char* name, FnCommandCallback_t callback, const char *help, int flags);
  void HookOrAddConCommand(const char* name, FnCommandCallback_t callback, const char *help, int flags);

public:
  void OnPluginStart();
};

#define CONMSG g_SMAPI->ConPrintf
#define CLIENT_CONMSG g_SMAPI->ClientConPrintf

extern SourceLuaConsole g_Console;

#endif // _INCLUDE_CONSOLE
