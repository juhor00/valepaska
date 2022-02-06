#include "player.h"

Player::Player(id id):
    Member(id),
    hand_(new HandCards)
{

}

Player::~Player()
{
    delete hand_;
}

