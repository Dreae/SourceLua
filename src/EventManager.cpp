#include "EventManager.hpp"
#include "luaruntime/LuaRuntime.hpp"

EventManager *g_EventManager;

EventManager::EventManager(SourceLua *sl) {
  this->sl = sl;
}

void EventManager::Hook_ClientCommand(edict_t *pEntity, const CCommand &args) {
  if(!pEntity || pEntity->IsFree()) {
    return;
  }

  g_LuaRuntime->FireClientCommand(g_Engine->IndexOfEdict(pEntity), args);
}
