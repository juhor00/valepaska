#ifndef PLAYER_H
#define PLAYER_H

#include "member.h"
#include "../cards/handcards.h"

class Player : public Member
{
public:
    Player(id id);
    ~Player();

private:

    HandCards* hand_;
};

#endif // PLAYER_H
