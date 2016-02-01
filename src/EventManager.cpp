#include "EventManager.hpp"
#include "luaruntime/LuaRuntime.hpp"

EventManager g_EventManager;

void EventManager::Hook_ClientCommand(edict_t *pEntity, const CCommand &args) {
  if(!pEntity || pEntity->IsFree()) {
    return;
  }

  g_LuaRuntime.FireClientCommand(g_Engine->IndexOfEdict(pEntity), args);
  RETURN_META(MRES_IGNORED);
}
