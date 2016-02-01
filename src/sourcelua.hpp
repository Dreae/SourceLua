/**
 * vim: set ts=4 sw=4 tw=99 noet :
 * ======================================================
 * Metamod:Source Stub Plugin
 * Written by AlliedModders LLC.
 * ======================================================
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * This stub plugin is public domain.
 */

#ifndef _INCLUDE_SOURCELUA
#define _INCLUDE_SOURCELUA

#include "wrapper.hpp"
#include "filesystem.h"

#if defined WIN32 && !defined snprintf
#define snprintf _snprintf
#endif

#define SOURCELUA_VERSION "0.0.2"

class SourceLua : public ISmmPlugin, public IMetamodListener
{
public:
	bool Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late);
	bool Unload(char *error, size_t maxlen);
	bool Pause(char *error, size_t maxlen);
	bool Unpause(char *error, size_t maxlen);
	void AllPluginsLoaded();
public: //IMetamodListener stuff
	void OnVSPListening(IServerPluginCallbacks *iface);
public:
	const char *GetAuthor();
	const char *GetName();
	const char *GetDescription();
	const char *GetURL();
	const char *GetLicense();
	const char *GetVersion();
	const char *GetDate();
	const char *GetLogTag();
};

class SourceLuaBase {
public:
	SourceLuaBase() {
		pLoaderNext = SourceLuaBase::head;
		SourceLuaBase::head = this;
	}
	virtual void OnPluginStart() { }
public:
	SourceLuaBase *pLoaderNext;
	static SourceLuaBase *head;
};

void Hook_ServerActivate(edict_t *pEdictList, int edictCount, int clientMax);

extern SourceLua g_SourceLua;
extern IServerGameClients *g_iGameClients;
extern IFileSystem *g_iFileSystem;
extern IVEngineServer *g_Engine;
extern IPlayerInfoManager *g_iPlayerInfo;
extern IServerPluginHelpers *g_iPluginHelpers;
extern IServerPluginCallbacks *vsp_callbacks;

PLUGIN_GLOBALVARS();

#endif //_INCLUDE_SOURCELUA
