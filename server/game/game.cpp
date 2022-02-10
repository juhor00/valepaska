#include "game.h"
#include "../handler.h"


Game::Game(Handler *handler):
    handler_(handler),
    deck_(new Deck),
    cardStack_(new CardStack),
    inTurn_(nullptr),
    lastClaim_(0),
    deckPlay_({Card(2, 'D'), false})
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

bool Game::play(Player *player, cards cards, int claimRank)
{
    if(not isInTurn(player)){
        return false;
    }
    if(not player->hasCards(cards)){
        return false;
    }
    if(not Card::isValidRank(claimRank)){
        return false;
    }
    if(not isValidPlay(cards, claimRank)){
        return false;
    }

    player->remove(cards);
    drawTo(player, DRAW_MIN);


    cardStack_->add(cards);

    //
    // DO SOMETHING WITH CLAIM
    //

    changeTurn();
    return true;
}

bool Game::play(id player, cards cards, int claimRank)
{
    return play(getPlayer(player), cards, claimRank);
}

void Game::deckPlay(id id)
{
    if(deckPlay_.played){
        handler_->print("Already played from deck!");
        return;
    }
    Player* player = getPlayer(id);
    if(isInTurn(player)){
        Card card = deck_->getTop();
        player->add({card});
        deckPlay_ = {card, true};
        handler_->deckEvent(card);
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
    if(not(0 < cards.size() && cards.size() <= DISCARD_LIMIT)){
        return false;
    }

    if(lastClaim_ == 2){
        if(cards.size() > 1){
            return false;
        }
    }
    if(claim == 10 || claim == 14 || claim == 2){
        if(cards.size() > 1){
            handler_->print("You can't play 2, 10 or Ace when over 1 card is selected");
            return false;
        }
    }
    if(deckPlay_.played){
        if(not cards.at(0).equals(deckPlay_.card) || cards.size() != 1){
            handler_->print("You can only play the card you picked up");
            return false;
        }
    }


    return isValidClaim(claim);
}

bool Game::isValidClaim(int claim)
{
    // No last claim
    if(lastClaim_ == 0){
        if(claim == 10 || claim == 14){
            handler_->print("10 or Ace can't be played when there are no played cards");
            return false;
        }
        if(not deck_->isEmpty()){
            if(claim > 10){
                handler_->print("Can't play court cards before deck is empty");
                return false;
            }
        }
        return true;
    }
    if(claim == 2){
        return true;
    }
    if(claim < lastClaim_){
        handler_->print("Can't play rank that is less than already played");
        return false;
    }
    if(lastClaim_ == 2){
        handler_->print("Only 2 can be played on top of 2");
        return false;
    }
    if(claim == 10){
        if(lastClaim_ > 9){
            handler_->print("10 can only be played if last played is 9 or lower");
            return false;
        }
    }
    if(claim == 14){
        if(lastClaim_ < 11){
            handler_->print("Ace can only be played if last played is Jack or higher");
            return false;
        }
    }
    if(lastClaim_ < 7){
        if(11 <= claim && claim <= 13){
            handler_->print("Court cards can only be played if last played is 7 or higher");
            return false;
        }
    }
    return true;


}
