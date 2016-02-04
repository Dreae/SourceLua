#ifndef _INCLUDE_CONSOLE
#define _INCLUDE_CONSOLE
#include <ISmmPlugin.h>
#include "sourcelua.hpp"
#include <functional>

typedef std::function<META_RES(const CCommand &)> CommandCallback;

class CommandHook {
public:
  CommandHook(ConCommand *cmd, CommandCallback callback);
  ~CommandHook();
  void Dispatch(const CCommand &cmd);
private:
  int hook_id;
  CommandCallback callback;
};

class SourceLuaConsole : public SourceLuaBase {
public:
  SourceLuaConsole() { };
  META_RES DispatchClientCmd(edict_t *client, const CCommand &command);
  CommandHook *RegConCommand(const char* name, CommandCallback callback, const char *help, int flags);
  CommandHook *HookOrAddConCommand(const char* name, CommandCallback callback, const char *help, int flags);

public:
  void OnPluginStart();
};

#define CONMSG g_SMAPI->ConPrintf
#define CLIENT_CONMSG g_SMAPI->ClientConPrintf

extern SourceLuaConsole g_Console;

#endif // _INCLUDE_CONSOLE
