#include "UserMessages.hpp"
#include "sourcelua.hpp"

UserMessages g_UserMsgs;

bf_write *UserMessages::StartBitBufMessage(int msg_id, const int players[], size_t playerNum, bool no_hook, bool reliable, bool init_msg) {
#ifdef USE_PROTOBUF_USERMESSAGES
  return NULL;
#else
  bf_write *buffer;

  this->no_hook = no_hook;
  recipientFilter.Initialize(players, playerNum);

  if(no_hook) {
#if SOURCE_ENGINE >= SE_LEFT4DEAD
    buffer = SH_CALL(g_Engine, &IVEngineServer::UserMessageBegin)(&recipientFilter, msg_id, g_SMAPI->GetUserMessage(msg_id));
#else
    buffer = SH_CALL(g_Engine, &IVEngineServer::UserMessageBegin)(&recipientFilter, msg_id);
#endif
  } else {
#if SOURCE_ENGINE >= SE_LEFT4DEAD
    buffer = g_Engine->UserMessageBegin(&recipientFilter, msg_id, g_SMAPI->GetUserMessage(msg_id));
#else
    buffer = g_Engine->UserMessageBegin(&recipientFilter, msg_id);
#endif
  }
  return buffer;
#endif
}

bool UserMessages::EndMessage() {
  if(this->no_hook) {
    SH_CALL(g_Engine, &IVEngineServer::MessageEnd)();
  } else {
    g_Engine->MessageEnd();
  }
  this->Reset();
  return true;
}

void UserMessages::Reset() {
  this->no_hook = false;
  this->recipientFilter.Reset();
}

int UserMessages::GetMessageIndex(const char *msg) {
#if SOURCE_ENGINE == SE_DOTA
  return g_DotaUsermessageHelpers.GetIndex(msg);
#elif SOURCE_ENGINE == SE_CSGO
  return g_Cstrike15UsermessageHelpers.GetIndex(msg);
#else
  return g_SMAPI->FindUserMessage(msg);
#endif
}
