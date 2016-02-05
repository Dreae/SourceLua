#include "GameHooks.hpp"
#include "EventManager.hpp"

GameHooks g_GameHooks;

#if SOURCE_ENGINE >= SE_ORANGEBOX
SH_DECL_HOOK2_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, edict_t *, const CCommand &);
#else
SH_DECL_HOOK1_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, edict_t *);
#endif

SH_DECL_HOOK1_void(IServerGameClients, SetCommandClient, SH_NOATTRIB, false, int);
SH_DECL_HOOK1_void(IServerGameDLL, GameFrame, SH_NOATTRIB, false, bool);

void GameHooks::OnPluginStart() {
  // TODO:20 Save hooks so they can be removed at shutdown?
  SH_ADD_HOOK(IServerGameClients, ClientCommand, g_iGameClients, SH_MEMBER(&g_EventManager, &EventManager::Hook_ClientCommand), false);
  SH_ADD_HOOK(IServerGameClients, SetCommandClient, g_iGameClients, SH_MEMBER(this, &GameHooks::SetCommandClient), false);
  SH_ADD_HOOK(IServerGameDLL, GameFrame, server, SH_MEMBER(this, &GameHooks::GameFrame), false);
}

int GameHooks::CommandClient() const {
  return last_command_client;
}

void GameHooks::SetCommandClient(int client) {
  last_command_client = client + 1;
}

void GameHooks::GameFrame(bool simulating) {
  
}
