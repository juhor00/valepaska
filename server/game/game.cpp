#include "game.h"


Game::Game(EventHandler *eventHandler):
    eventHandler_(eventHandler)
{

}

bool Game::add(id id)
{
    return Group::add(new Player(id));
}

Player *Game::getPlayer(id id)
{
    return (Player*) getMember(id);
}
