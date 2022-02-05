#ifndef HANDCARDS_H
#define HANDCARDS_H

#include "cardcollection.h"
#include <unordered_set>

using cards = std::unordered_set<Card>;

class HandCards : public CardCollection
{
public:
    HandCards();

    void add(Card card);
    void add(cards cards);
    void remove(Card card);
    void remove(cards cards);
    bool hasCards(cards cards);
};

#endif // HANDCARDS_H
