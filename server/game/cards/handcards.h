#ifndef HANDCARDS_H
#define HANDCARDS_H

#include "cardcollection.h"

class HandCards : public CardCollection
{
public:
    HandCards();

    bool add(Card card) override;
    bool add(cards cards);
    bool remove(Card card) override;
    bool remove(cards cards);
    bool hasCards(cards cards);
    void clear();
};

#endif // HANDCARDS_H
