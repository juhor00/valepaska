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

void Player::add(cards cards)
{
    hand_->add(cards);
}

void Player::remove(cards cards)
{
    hand_->remove(cards);
}

bool Player::hasCards(cards cards)
{
    return hand_->hasCards(cards);
}
