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
    return static_cast<Player*>(getMember(id));
}

std::vector<Player *> Game::getPlayers()
{
    std::vector<Player*> players;
    for(Member* member : getMembers()){
        players.push_back(static_cast<Player*>(member));
    }
    return players;
}

Player *Game::changeTurn()
{
    return static_cast<Player*>(next());
}

void Game::draw(Player *player)
{
    draw(player, 1);
}

void Game::draw(Player *player, int amount)
{

}
