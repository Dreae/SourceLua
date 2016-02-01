#ifndef _INCLUDE_GAMEHOOKS
#define _INCLUDE_GAMEHOOKS
#include <ISmmPlugin.h>
#include "sourcelua.hpp"

class GameHooks : public SourceLuaBase {
public:
  GameHooks() { };

public:
  void OnPluginStart();
};

extern GameHooks g_GameHooks;

#endif // _INCLUDE_GAMEHOOKS
