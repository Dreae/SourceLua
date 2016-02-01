#ifndef _INCLUDE_EVENTMANAGER
#define _INCLUDE_EVENTMANAGER

#include "sourcelua.hpp"

class EventManager : public SourceLuaBase {
public:
  EventManager() { };
	void Hook_ClientCommand(edict_t *pEntity, const CCommand &args);
};

extern EventManager g_EventManager;

#endif // _INCLUDE_EVENTMANAGER
