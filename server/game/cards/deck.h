#ifndef DECK_H
#define DECK_H

#include "cardcollection.h"
#include <algorithm>
#include <random>
#include <chrono>

const int DECK_SIZE = 52;

class Deck : public CardCollection
{
public:
    Deck();
    Card getTop();
    void generateFull();
    void shuffle();
    bool add(const Card card) override;
    bool remove(const Card card) override;

private:

    std::vector<Card> cards_;

};

#endif // DECK_H
