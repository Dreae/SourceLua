#ifndef _INCLUDE_CONSOLE
#define _INCLUDE_CONSOLE
#include <ISmmPlugin.h>
#include "sourcelua.hpp"

class SourceLuaConsole : public SourceLuaBase {
public:
  SourceLuaConsole() { };

public:
  void OnPluginStart();
};

extern SourceLuaConsole g_Console;

#endif // _INCLUDE_CONSOLE
