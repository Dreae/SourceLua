#ifndef _INCLUDE_CONSOLE
#define _INCLUDE_CONSOLE
#include <ISmmPlugin.h>
#include "sourcelua.hpp"

class SourceLuaConsole : public SourceLuaBase {
public:
  SourceLuaConsole() { };
  META_RES DispatchClientCmd(edict_t *client, const CCommand &command);

public:
  void OnPluginStart();
};

#define CONMSG g_SMAPI->ConPrintf
#define CLIENT_CONMSG g_SMAPI->ClientConPrintf

extern SourceLuaConsole g_Console;

#endif // _INCLUDE_CONSOLE
