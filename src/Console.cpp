#include "Console.hpp"
#include "convar.h"
#include "GameHooks.hpp"
#include "luaruntime/LuaRuntime.hpp"

SourceLuaConsole g_Console;

SH_DECL_HOOK1_void(ConCommand, Dispatch, SH_NOATTRIB, 0, const CCommand &)

void sourcelua_concmd(const CCommand &command) {
  int args = command.ArgC();
  if(args >= 2) {
    const char *cmd = command.Arg(1);
    if(strcmp(cmd, "version") == 0) {
      CONMSG("SourceLua v%s\n", SOURCELUA_VERSION);
      CONMSG("  - %s\n", LUAJIT_VERSION);
      CONMSG("  - %s\n", LUA_VERSION);
    }
  }
}

void sourcelua_clientcmd(edict_t *client, const CCommand &command) {
  CLIENT_CONMSG(client, "Nothing here");
}

void SourceLuaConsole::OnPluginStart() {
  ConCommandBase *sourcelua = new ConCommand("sourcelua", sourcelua_concmd, "Manage SourceLua", FCVAR_NONE);
  META_REGCVAR(sourcelua);
}

META_RES SourceLuaConsole::DispatchClientCmd(edict_t *client, const CCommand &command) {
  if(strcmp(command.Arg(0), "sourcelua") == 0) {
    sourcelua_clientcmd(client, command);
    return MRES_SUPERCEDE;
  } else {
    // #TODO: Better way to dispatch commands
    g_LuaRuntime.FireClientCommand(g_Engine->IndexOfEdict(client), command);
    return MRES_IGNORED;
  }
}

void SourceLuaConsole::HookOrAddConCommand(const char* name, FnCommandCallback_t callback, const char *help, int flags) {
  ConCommand *current = g_iCVar->FindCommand(name);
  if(!current) {
    CONMSG("Registering %s\n", name);
    RegConCommand(name, callback, help, flags);
  } else {
    CONMSG("Command %s already exists, hooking\n", name);
    SH_ADD_HOOK(ConCommand, Dispatch, current, SH_STATIC(callback), false);
  }
}

void SourceLuaConsole::RegConCommand(const char* name, FnCommandCallback_t callback, const char *help, int flags) {
  ConCommandBase *cmd = new ConCommand(name, callback, help, flags);
  META_REGCVAR(cmd);
}
