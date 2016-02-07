#ifndef _INCLUDE_USERMESSAGES
#define _INCLUDE_USERMESSAGES

#include <bitbuf.h>
#include <irecipientfilter.h>
#include "sourcelua.hpp"
#include "RecipientFilter.hpp"

class UserMessages : public SourceLuaBase {
public:
  UserMessages() { };
  bool EndMessage();
  int GetMessageIndex(const char *msg);
  bf_write *StartBitBufMessage(int msg_id, const int players[], unsigned int playerNum, bool no_hook, bool reliable, bool init_msg);
  void Reset();
private:
  CRecipientFilter recipientFilter;
  bool no_hook;
};

extern UserMessages g_UserMsgs;

#endif // _INCLUDE_USERMESSAGES
