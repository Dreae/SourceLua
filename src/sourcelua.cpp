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
#include "luaruntime/LuaRuntime.hpp"

SH_DECL_HOOK3_void(IServerGameDLL, ServerActivate, SH_NOATTRIB, 0, edict_t *, int, int);

SourceLua g_SourceLua;
IServerGameDLL *server = NULL;
LuaRuntime *g_LuaRuntime;

PLUGIN_EXPOSE(SourceLua, g_SourceLua);
bool SourceLua::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();
	this->mm_api = ismm;

	GET_V_IFACE_ANY(GetServerFactory, server, IServerGameDLL, INTERFACEVERSION_SERVERGAMEDLL);
	GET_V_IFACE_ANY(GetServerFactory, this->gameclients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);

	SH_ADD_HOOK_STATICFUNC(IServerGameDLL, ServerActivate, server, Hook_ServerActivate, true);

	this->eventmanager = new EventManager(this);

	this->gamehooks = new GameHooks(this);
	this->gamehooks->Start();

	return true;
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

void SourceLua::AllPluginsLoaded()
{
	g_LuaRuntime = new LuaRuntime(this);
	g_LuaRuntime->Init();
	luaL_dostring(g_LuaRuntime->L, "print('butts')");
	luaL_dostring(g_LuaRuntime->L, "Logger:info('butts2')");
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
