#include "GameHooks.hpp"
#include "EventManager.hpp"

GameHooks g_GameHooks;

#if SOURCE_ENGINE >= SE_ORANGEBOX
SH_DECL_HOOK2_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, edict_t *, const CCommand &);
#else
SH_DECL_HOOK1_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, edict_t *);
#endif

SH_DECL_HOOK1_void(IServerGameClients, SetCommandClient, SH_NOATTRIB, false, int);

void GameHooks::OnPluginStart() {
  // TODO:20 Save hooks so they can be removed at shutdown?
  SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientCommand, g_iGameClients, &g_EventManager, &EventManager::Hook_ClientCommand, false);
  SH_ADD_HOOK_MEMFUNC(IServerGameClients, SetCommandClient, g_iGameClients, &g_GameHooks, &GameHooks::SetCommandClient, false);
}

int GameHooks::CommandClient() const {
  return last_command_client;
}

void GameHooks::SetCommandClient(int client) {
  last_command_client = client + 1;
}
