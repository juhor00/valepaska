#ifndef DECK_H
#define DECK_H

#include "cardcollection.h"
#include <algorithm>
#include <random>

const int DECK_SIZE = 52;

class Deck : public CardCollection
{
public:
    Deck();
    Card getTop();
    void generateFull();
    void shuffle();

private:

};

#endif // DECK_H
