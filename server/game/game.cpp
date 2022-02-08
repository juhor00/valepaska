#include "game.h"


Game::Game(EventHandler *eventHandler):
    eventHandler_(eventHandler),
    deck_(new Deck),
    cardStack_(new CardStack)
{

}

Game::Game():
    Game(nullptr)
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

void Game::initGame()
{
    // Deck and cardstack
    deck_->generateFull();
    deck_->shuffle();
    cardStack_->clear();

    // Players
    TurnOrder::shuffle();

    for(Member* member : getMembersInOrder()){
        Player* player = static_cast<Player*>(member);
        player->clear();
        drawTo(player, DRAW_MIN);
    }
}

void Game::print()
{
    std::cout << "----Game state----" << std::endl;
    std::cout << std::endl;
    std::cout << "--Deck--" << std::endl;
    deck_->print();
    std::cout << "--Deck--" << std::endl;
    std::cout << std::endl;
    std::cout << "--CardStack--" << std::endl;
    cardStack_->print();
    std::cout << "--CardStack--" << std::endl;
    std::cout << std::endl;
    std::cout << "--Players--" << std::endl;
    for(Member* member : getMembersInOrder()){
        Player* player = static_cast<Player*>(member);
        if(isInTurn(player)){
            std::cout << "[+] ";
        } else {
            std::cout << "[ ] ";
        }
        player->print();
        std::cout << std::endl;
    }
    std::cout << "--Players--" << std::endl;
    std::cout << std::endl;
}

void Game::play(Player *player, cards cards, int claimRank)
{
    if(not isInTurn(player)){
        return;
    }
    if(not player->hasCards(cards)){
        return;
    }
    if(not Card::isValidRank(claimRank)){
        return;
    }

    player->remove(cards);
    drawTo(player, DRAW_MIN);


    cardStack_->add(cards);

    //
    // DO SOMETHING WITH CLAIM
    //

    changeTurn();
}

void Game::play(id player, cards cards, int claimRank)
{
    play(getPlayer(player), cards, claimRank);
}

void Game::draw(Player *player)
{
    draw(player, 1);
}

void Game::draw(Player *player, int amount)
{
    cards cards;
    for(int i=0; i<amount; i++){
        if(not deck_->isEmpty()){
            cards.push_back(deck_->getTop());
        }

    }
    player->add(cards);
}

void Game::drawTo(Player *player, int target)
{
    int amount = target - player->getCardCount();
    draw(player, amount);
}

void Game::takeLatest(Player *player)
{
    player->add(cardStack_->getLatest());

}
