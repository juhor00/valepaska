#ifndef PLAYER_H
#define PLAYER_H

#include "member.h"
#include "../cards/handcards.h"

class Player : public Member
{
public:
    Player(id id);
    ~Player();

    void add(cards cards);
    void remove(cards cards);
    bool hasCards(cards cards);
    int getCardCount();
    void print();
    void clear();

private:

    HandCards* hand_;
};

#endif // PLAYER_H
