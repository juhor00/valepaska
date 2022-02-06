#ifndef HANDCARDS_H
#define HANDCARDS_H

#include "cardcollection.h"
#include <set>

using cards = std::set<Card>;

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
};

#endif // HANDCARDS_H
