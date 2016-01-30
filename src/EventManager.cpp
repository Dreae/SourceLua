#include "EventManager.hpp"

EventManager *g_EventManager;

EventManager::EventManager(SourceLua *sl) {
  this->sl = sl;
}

void EventManager::Hook_ClientCommand(edict_t *pEntity, const CCommand &args) {
  META_LOG(g_PLAPI, "Got client command %s", args.Arg(0));
}
