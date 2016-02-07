#ifndef _INCLUDE_CHATMANAGER
#define _INCLUDE_CHATMANAGER

#define TEXTMSG_DEST_NOTIFY  1
#define TEXTMSG_DEST_CONSOLE 2
#define TEXTMSG_DEST_CHAT    3
#define TEXTMSG_DEST_CENTER  4

#include "sourcelua.hpp"

class ChatManager : public SourceLuaBase {
public:
  ChatManager() { };
  void PrintToChat(int player, const char *message);
  void PrintToChatAll(const char *message);
};

extern ChatManager g_ChatManager;

#endif // _INCLUDE_CHATMANAGER
