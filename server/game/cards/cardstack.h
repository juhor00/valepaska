#ifndef CARDSTACK_H
#define CARDSTACK_H

#include "cardcollection.h"
#include <vector>

class CardStack : public CardCollection
{
public:
    CardStack();

    void add(Card card);
    void add(cards cards);
    void clear();

    cards getLatest();
    cards getAll();

private:

    cards latestCards_;
};

#endif // CARDSTACK_H
