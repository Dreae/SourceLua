#include "GameHooks.hpp"
#include "EventManager.hpp"

GameHooks g_GameHooks;

#if SOURCE_ENGINE >= SE_ORANGEBOX
SH_DECL_HOOK2_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, edict_t *, const CCommand &);
#else
SH_DECL_HOOK1_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, edict_t *);
#endif

void GameHooks::OnPluginStart() {
  SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientCommand, g_iGameClients, &g_EventManager, &EventManager::Hook_ClientCommand, false);
}
