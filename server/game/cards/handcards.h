#ifndef HANDCARDS_H
#define HANDCARDS_H

#include "cardcollection.h"

class HandCards : public CardCollection
{
public:
    HandCards();

    void add(Card card);
    void add(cards cards);
    void remove(Card card);
    void remove(cards cards);
    bool hasCards(cards cards);
    void moveTo(CardCollection* other, cards cards);
    void clear();
};

#endif // HANDCARDS_H
