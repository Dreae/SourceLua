#include "Console.hpp"
#include "convar.h"
#include "GameHooks.hpp"
#include "luaruntime/LuaRuntime.hpp"

SourceLuaConsole g_Console;

SH_DECL_HOOK1_void(ConCommand, Dispatch, SH_NOATTRIB, 0, const CCommand &);

void ignore_con_cmd(const CCommand &command) {
  RETURN_META(MRES_IGNORED);
}

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
    return g_LuaRuntime.FireClientCommand(g_Engine->IndexOfEdict(client), command);
  }
}

CommandHook *SourceLuaConsole::HookOrAddConCommand(const char* name, CommandCallback callback, const char *help, int flags) {
  ConCommand *current = g_iCVar->FindCommand(name);
  if(!current) {
    CONMSG("Registering %s\n", name);
    return RegConCommand(name, callback, help, flags);
  } else {
    CONMSG("Command %s already exists, hooking\n", name);
    return new CommandHook(current, callback);
  }
}

CommandHook *SourceLuaConsole::RegConCommand(const char* name, CommandCallback callback, const char *help, int flags) {
  ConCommand *cmd = new ConCommand(name, ignore_con_cmd, help, flags);
  META_REGCVAR((ConCommandBase *)cmd);
  return new CommandHook(cmd, callback);
}


CommandHook::CommandHook(ConCommand *cmd, CommandCallback cb) {
  this->callback = cb;
  this->hook_id = 0;
  this->hook_id = SH_ADD_HOOK(ConCommand, Dispatch, cmd, SH_MEMBER(this, &CommandHook::Dispatch), false);
}

CommandHook::~CommandHook() {
  if(this->hook_id) {
    SH_REMOVE_HOOK_ID(this->hook_id);
  }
}

void CommandHook::Dispatch(const CCommand &cmd) {
  RETURN_META(this->callback(cmd));
}
