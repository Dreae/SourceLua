#include "Console.hpp"
#include "convar.h"
#include "GameHooks.hpp"

SourceLuaConsole g_Console;

void sourcelua_concmd(const CCommand &command) {
  if(command.ArgC() == 1) {
    META_LOG(g_PLAPI, "Got version check from %d", g_GameHooks.CommandClient());
    Warning("Nope");
  }
}

void SourceLuaConsole::OnPluginStart() {
  // #FIXME: Not usable by client
  ConCommandBase *sourcelua = new ConCommand("sourcelua", sourcelua_concmd, "Manage SourceLua", FCVAR_NONE);
  META_REGCVAR(sourcelua);
}
