#ifndef _INCLUDE_RECIPIENTFILTER
#define _INCLUDE_RECIPIENTFILTER

#include <irecipientfilter.h>
#include <vector>

class CRecipientFilter : public IRecipientFilter {
public:
  CRecipientFilter() { Reset(); };
  void Initialize(const int players[], std::size_t numPlayers);
public:
  bool IsReliable() const;
  bool IsInitMessage() const;
  int GetRecipientCount() const;
  int GetRecipientIndex(int slot) const;

public:
  void MakeReliable();
  void MakeInit();
  void Reset();

private:
  std::vector<int> recipients;
  bool isReliable;
  bool isInitMessage;
  std::size_t size;
};

#endif // _INCLUDE_RECIPIENTFILTER
