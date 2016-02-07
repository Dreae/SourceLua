#include "ChatManager.hpp"
#include "UserMessages.hpp"

ChatManager g_ChatManager;

void ChatManager::PrintToChat(int client, const char *msg) {
  const int players[] = { client };
  bf_write *bitBuf = g_UserMsgs.StartBitBufMessage(g_UserMsgs.GetMessageIndex("SayText"), players, 1, true, true, false);
  bitBuf->WriteByte(0);
  bitBuf->WriteString(msg);
  bitBuf->WriteByte(true);

  g_UserMsgs.EndMessage();
}
