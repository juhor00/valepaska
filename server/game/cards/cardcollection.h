#ifndef CARDCOLLECTION_H
#define CARDCOLLECTION_H

#include "card.h"
#include <iostream>
#include <unordered_set>

using cards = std::unordered_set<Card>;

class CardCollection
{
public:
    CardCollection();
    virtual ~CardCollection();


    int size();
    bool hasCard(const Card card) const;
    bool isEmpty();
    void print();

protected:

    virtual bool add(const Card card);
    virtual bool remove(const Card card);
    void clear();
    cards getAll();

private:

    cards cards_;
};

#endif // CARDCOLLECTION_H
