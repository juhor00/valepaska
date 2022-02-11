#ifndef CARDSTACK_H
#define CARDSTACK_H

#include "cardcollection.h"
#include <vector>

class CardStack : public CardCollection
{
public:
    CardStack();

    bool add(Card card) override;
    bool add(cards cards);
    void clear();

    cards getLatest();
    cards getAll();

private:

    cards latestCards_;
};

#endif // CARDSTACK_H
