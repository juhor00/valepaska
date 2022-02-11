#ifndef HANDLER_H
#define HANDLER_H

#include "game/game.h"

class Handler
{
public:

    virtual void deckEvent(Card card)=0;
    virtual void print(std::string message)=0;
    virtual void pendingDiscard()=0;
};

#endif // HANDLER_H
