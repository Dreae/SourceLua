#include "RecipientFilter.hpp"

void CRecipientFilter::Initialize(const int players[], std::size_t numPlayers) {
  for(std::size_t c = 0; c < numPlayers; c++) {
    recipients.push_back(players[c]);
  }
  size = numPlayers;
}

int CRecipientFilter::GetRecipientIndex(int slot) const {
  if(slot < 0 || slot > size) {
    return -1;
  }
  return recipients[slot];
}

int CRecipientFilter::GetRecipientCount() const {
  return size;
}

bool CRecipientFilter::IsReliable() const {
  return isReliable;
}

bool CRecipientFilter::IsInitMessage() const {
  return isInitMessage;
}

void CRecipientFilter::MakeReliable() {
  isReliable = true;
}

void CRecipientFilter::MakeInit() {
  isInitMessage = true;
}

void CRecipientFilter::Reset() {
  isReliable = false;
  isInitMessage = false;
  recipients.clear();
}
