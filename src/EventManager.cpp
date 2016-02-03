#include "EventManager.hpp"
#include "luaruntime/LuaRuntime.hpp"
#include "Console.hpp"

EventManager g_EventManager;

void EventManager::Hook_ClientCommand(edict_t *pEntity, const CCommand &args) {
  if(!pEntity || pEntity->IsFree()) {
    return;
  }

  RETURN_META(g_Console.DispatchClientCmd(pEntity, args));
}
