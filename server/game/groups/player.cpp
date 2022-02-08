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

int Player::getCardCount()
{
    return hand_->size();
}

void Player::print()
{
    std::cout << "Player " << getId() << " cards:" << std::endl;
    hand_->print();
}

void Player::clear()
{
    hand_->clear();
}
