#ifndef _INCLUDE_WRAPPER
#define _INCLUDE_WRAPPER

#include <ISmmPlugin.h>
#include "iplayerinfo.h"

#if SOURCE_ENGINE <= SE_DARKMESSIAH
/**
 * Wrap the CCommand class so our code looks the same on all engines.
 */
class CCommand
{
public:
	const char *ArgS()
	{
		return engine->Cmd_Args();
	}
	int ArgC()
	{
		return engine->Cmd_Argc();
	}

	const char *Arg(int index)
	{
		return engine->Cmd_Argv(index);
	}
};

#define CVAR_INTERFACE_VERSION VENGINE_CVAR_INTERFACE_VERSION
#endif

#endif // _INCLUDE_WRAPPER
