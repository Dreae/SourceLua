#ifndef _INCLUDE_GAMEHOOKS
#define _INCLUDE_GAMEHOOKS
#include <ISmmPlugin.h>
#include "sourcelua.hpp"

class GameHooks {
public:
  GameHooks(SourceLua *sl);
  void Start();
private:
  SourceLua *sl;
};

#endif // _INCLUDE_GAMEHOOKS
