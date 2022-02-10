#ifndef HANDLER_H
#define HANDLER_H

#include "game/game.h"

class Handler
{
public:
    Handler();

    virtual void deckEvent(Card card)=0;
};

#endif // HANDLER_H
