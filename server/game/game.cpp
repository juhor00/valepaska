#include "game.h"
#include "../handler.h"


Game::Game(Handler *handler):
    handler_(handler),
    deck_(new Deck),
    cardStack_(new CardStack),
    inTurn_(nullptr),
    lastClaim_(0)
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
    if(not isValidPlay(cards, claimRank)){
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

void Game::deckPlay(id player)
{
    if(isInTurn(player)){
        handler_->deckEvent(deck_->getTop());
    }
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

bool Game::isValidPlay(cards cards, int claim)
{
    if(0 < cards.size() && cards.size() <= DISCARD_LIMIT){
        if(lastClaim_ == 2){
            if(cards.size() > 1){
                return false;
            }
        }
        if(claim == 10 || claim == 14){
            if(cards.size() > 1){
                return false;
            }
        }
        return isValidClaim(claim);
    }
    return false;
}

bool Game::isValidClaim(int claim)
{
    // No last claim
    if(lastClaim_ == 0){
        if(claim == 10 || claim == 14){
            return false;
        }
        if(not deck_->isEmpty()){
            if(claim > 10){
                return false;
            }
        }
        return true;
    }
    if(claim == 2){
        return true;
    }
    if(claim < lastClaim_){
        return false;
    }
    if(lastClaim_ == 2){
        return false;
    }
    if(claim == 10){
        if(lastClaim_ > 9){
            return false;
        }
    }
    if(claim == 14){
        if(lastClaim_ < 11){
            return false;
        }
    }
    if(lastClaim_ < 7){
        if(11 <= claim && claim <= 13){
            return false;
        }
    }
    return true;


}
