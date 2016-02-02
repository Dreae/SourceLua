#ifndef _INCLUDE_GAMEHOOKS
#define _INCLUDE_GAMEHOOKS
#include <ISmmPlugin.h>
#include "sourcelua.hpp"

class GameHooks : public SourceLuaBase {
public:
  GameHooks() { };
  int CommandClient() const;
  void SetCommandClient(int client);
public:
  void OnPluginStart();

private:
  int last_command_client;
};

extern GameHooks g_GameHooks;

#endif // _INCLUDE_GAMEHOOKS
