#ifndef _INCLUDE_GAMEHOOKS
#define _INCLUDE_GAMEHOOKS
#include <ISmmPlugin.h>
#include "sourcelua.hpp"
#include <functional>

typedef std::function<void(bool)> FrameHook;

class GameHooks : public SourceLuaBase {
public:
  GameHooks() { };
  int CommandClient() const;
  void SetCommandClient(int client);
  void GameFrame(bool simulating);
public:
  void OnPluginStart();

private:
  int last_command_client;
  std::list<FrameHook> frame_hooks;
};

extern GameHooks g_GameHooks;

#endif // _INCLUDE_GAMEHOOKS
