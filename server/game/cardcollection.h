#ifndef CARDCOLLECTION_H
#define CARDCOLLECTION_H

#include "card.h"
#include <deque>

class CardCollection
{
public:
    CardCollection();


    int size();
    bool hasCard(Card card);
    bool isEmpty();

protected:

    void add(Card card);
    Card getLast();
    Card getFirst();

private:

    std::deque<Card> cards_;
};

#endif // CARDCOLLECTION_H
