#ifndef CARDSTACK_H
#define CARDSTACK_H

#include "cardcollection.h"
#include <vector>

class CardStack : public CardCollection
{
public:
    CardStack();

    void add(Card card);
    void add(std::vector<Card> cards);
    void clear();

    std::vector<Card> getLatest();

private:

    std::vector<Card> latestCards_;
};

#endif // CARDSTACK_H
