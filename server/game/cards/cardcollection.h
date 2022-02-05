#ifndef CARDCOLLECTION_H
#define CARDCOLLECTION_H

#include "card.h"
#include <deque>
#include <iostream>

class CardCollection
{
public:
    CardCollection();


    int size();
    bool hasCard(Card card);
    bool isEmpty();
    void print();

protected:

    void add(Card card);
    Card getLast();
    Card getFirst();
    void clear();
    std::deque<Card>::iterator begin();
    std::deque<Card>::iterator end();

private:

    std::deque<Card> cards_;
};

#endif // CARDCOLLECTION_H
