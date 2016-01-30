#ifndef _INCLUDE_EVENTMANAGER
#define _INCLUDE_EVENTMANAGER

#include "sourcelua.hpp"

class EventManager {
public:
  EventManager(SourceLua *sl);
	void Hook_ClientCommand(edict_t *pEntity, const CCommand &args);
private:
  SourceLua *sl;
};

extern EventManager *g_EventManager;

#endif // _INCLUDE_EVENTMANAGER
