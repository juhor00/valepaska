#include "game.h"


Game::Game(EventHandler *eventHandler):
    eventHandler_(eventHandler)
{

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
