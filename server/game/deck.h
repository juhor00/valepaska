#ifndef DECK_H
#define DECK_H

#include "cardcollection.h"

const int DECK_SIZE = 52;

class Deck : public CardCollection
{
public:
    Deck();
    Card getTop();
    void generateFull();

private:

};

#endif // DECK_H
