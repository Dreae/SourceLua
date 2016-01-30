#include "GameHooks.hpp"

#if SOURCE_ENGINE >= SE_ORANGEBOX
SH_DECL_HOOK2_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, edict_t *, const CCommand &);
#else
SH_DECL_HOOK1_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, edict_t *);
#endif

GameHooks::GameHooks(SourceLua *sl) {
  this->sl = sl;
}

void GameHooks::Start() {
  SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientCommand, this->sl->gameclients, this->sl->eventmanager, &EventManager::Hook_ClientCommand, false);
}
