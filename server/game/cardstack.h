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
};

#endif // CARDSTACK_H
