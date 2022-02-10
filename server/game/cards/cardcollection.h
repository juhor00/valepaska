#ifndef CARDCOLLECTION_H
#define CARDCOLLECTION_H

#include "card.h"
#include <deque>
#include <iostream>
#include <vector>

using cards = std::vector<Card>;

class CardCollection
{
public:
    CardCollection();


    int size();
    bool hasCard(const Card card) const;
    bool isEmpty();
    void print();

protected:

    void moveTo(CardCollection* other, Card card);
    void moveAllTo(CardCollection* other);
    void add(const Card card);
    void remove(const Card card);
    Card getLast();
    Card getFirst();
    void clear();
    cards getAll();
    cards::iterator begin();
    cards::iterator end();

private:

    cards cards_;
};

#endif // CARDCOLLECTION_H
