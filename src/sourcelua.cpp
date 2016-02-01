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

#include <stdio.h>
#include "sourcelua.hpp"
#include "EventManager.hpp"
#include "luaruntime/LuaRuntime.hpp"

SH_DECL_HOOK3_void(IServerGameDLL, ServerActivate, SH_NOATTRIB, 0, edict_t *, int, int);

SourceLua g_SourceLua;
IServerGameDLL *server = NULL;
SourceLuaBase *SourceLuaBase::head = NULL;

IServerGameClients *g_iGameClients;
IFileSystem *g_iFileSystem;
IVEngineServer *g_Engine;
IPlayerInfoManager *g_iPlayerInfo;
IServerPluginHelpers *g_iPluginHelpers;

IServerPluginCallbacks *vsp_callbacks;

PLUGIN_EXPOSE(SourceLua, g_SourceLua);
bool SourceLua::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();

	GET_V_IFACE_CURRENT(GetEngineFactory, g_Engine, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
	GET_V_IFACE_CURRENT(GetServerFactory, g_iPlayerInfo, IPlayerInfoManager, INTERFACEVERSION_PLAYERINFOMANAGER);
	GET_V_IFACE_CURRENT(GetEngineFactory, g_iPluginHelpers, IServerPluginHelpers, INTERFACEVERSION_ISERVERPLUGINHELPERS);

	GET_V_IFACE_ANY(GetServerFactory, server, IServerGameDLL, INTERFACEVERSION_SERVERGAMEDLL);
	GET_V_IFACE_ANY(GetServerFactory, g_iGameClients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
	GET_V_IFACE_ANY(GetFileSystemFactory, g_iFileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);

	if ((vsp_callbacks = ismm->GetVSPInfo(NULL)) == NULL)	{
		ismm->AddListener(this, this);
		ismm->EnableVSPListener();
	}


	SH_ADD_HOOK_STATICFUNC(IServerGameDLL, ServerActivate, server, Hook_ServerActivate, true);

	SourceLuaBase *pLoader = SourceLuaBase::head;
	while(pLoader) {
		pLoader->OnPluginStart();
		pLoader = pLoader->pLoaderNext;
	}

	return true;
}

void SourceLua::OnVSPListening(IServerPluginCallbacks *iface) {
	vsp_callbacks = iface;
}

bool SourceLua::Unload(char *error, size_t maxlen)
{
	SH_REMOVE_HOOK_STATICFUNC(IServerGameDLL, ServerActivate, server, Hook_ServerActivate, true);

	return true;
}

void Hook_ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
	META_LOG(g_PLAPI, "ServerActivate() called: edictCount = %d, clientMax = %d", edictCount, clientMax);
}

void SourceLua::AllPluginsLoaded() {
 	g_LuaRuntime.LoadAddons();
}

bool SourceLua::Pause(char *error, size_t maxlen)
{
	return true;
}

bool SourceLua::Unpause(char *error, size_t maxlen)
{
	return true;
}

const char *SourceLua::GetLicense()
{
	return "MIT";
}

const char *SourceLua::GetVersion()
{
	return SOURCELUA_VERSION;
}

const char *SourceLua::GetDate()
{
	return __DATE__;
}

const char *SourceLua::GetLogTag()
{
	return "SourceLua";
}

const char *SourceLua::GetAuthor()
{
	return "Dreae";
}

const char *SourceLua::GetDescription()
{
	return "Source engine scripting in Lua";
}

const char *SourceLua::GetName()
{
	return "Source Lua";
}

const char *SourceLua::GetURL()
{
	return "https://github.com/dreae";
}
