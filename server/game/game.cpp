#include "game.h"


Game::Game(EventHandler *eventHandler):
    eventHandler_(eventHandler),
    deck_(new Deck),
    cardStack_(new CardStack)
{

}

Game::~Game()
{
    delete deck_;
    delete cardStack_;
}

bool Game::add(id id)
{
    return TurnOrder::add(new Player(id));
}

bool Game::add(Member *member)
{
    return add(member->getId());
}

Player *Game::getPlayer(id id)
{
    return (Player*) getMember(id);
}
