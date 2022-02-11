#include "game.h"
#include "../handler.h"


Game::Game(Handler *handler):
    handler_(handler),
    deck_(new Deck),
    cardStack_(new CardStack),
    claims_({}),
    deckPlay_({Card(2, 'D'), false}),
    discardID_(0)
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
    return dynamic_cast<Player*>(getMember(id));
}

std::vector<Player *> Game::getPlayers()
{
    std::vector<Player*> players;
    for(Member* member : getMembers()){
        players.push_back(dynamic_cast<Player*>(member));
    }
    return players;
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
        Player* player = dynamic_cast<Player*>(member);
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
        Player* player = dynamic_cast<Player*>(member);
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

bool Game::play(id player, cards cards, int claimRank)
{
    return play(getPlayer(player), cards, claimRank);
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

    // Cards
    player->remove(cards);
    drawTo(player, DRAW_MIN);
    cardStack_->add(cards);

    // Claim
    claims_.push_back({claimRank, (int) cards.size(), player});

    // Turn
    TurnOrder::next();

    // Discard
    if(toDiscard()){
        handler_->pendingDiscard(++discardID_);
    }
    return true;
}

void Game::deckPlay(id id)
{
    Player* player = getPlayer(id);
    deckPlay(player);

}

void Game::deckPlay(Player *player)
{
    if(isInTurn(player)){
        if(deckPlay_.played){
            handler_->print("Already played from deck!");
            return;
        }
        Card card = deck_->getTop();
        player->add({card});
        deckPlay_ = {card, true};
        handler_->deckEvent(card);
    }
}

bool Game::suspect(id player)
{
    return suspect(getPlayer(player));
}

bool Game::suspect(Player *player)
{
    if(deck_->isEmpty()){
        handler_->print("Cannot suspect when deck is empty");
        return false;
    }
    claim claim = claims_.back();
    Player* claimer = claim.claimer;
    if(player == claimer){
        handler_->print("Claimer cannot suspect");
        return false;
    }

    bool lied = false;
    for(Card card : cardStack_->getLatest()){
        if(card.rank() != claim.rank){
            lied = true;
        }
    }
    if(lied){
        // Claimer loses
        handler_->print("Claimer lied");
        takeAll(claimer);
        turnTo(player);

    } else {
        // Suspecter loses
        handler_->print("Claim was right, suspecter takes cards");
        takeAll(player);
        turnTo(claimer);
    }
    return true;
}

bool Game::discard(discardID id)
{
    if(id != discardID_){
        return false;
    }
    if(not toDiscard()){
        return false;
    }
    cardStack_->clear();
    turnTo(claims_.back().claimer);
    claims_.clear();

    // Handle win
    return true;
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
            cards.insert(deck_->getTop());
        }

    }
    player->add(cards);
}

void Game::drawTo(Player *player, int target)
{
    int amount = target - player->getCardCount();
    draw(player, amount);
}

void Game::takeAll(Player *player)
{
    player->add(cardStack_->getAll());

}

bool Game::toDiscard()
{
    if(cardStack_->isEmpty()){
        return false;
    }

    // Discard cards
    claim claim = claims_.back();
    if(claim.rank == 10 || claim.rank == 14){
        return true;
    }
    // Never discard 2's
    if(claim.rank == 2){
        return false;
    }
    if(cardStack_->size() < DISCARD_LIMIT){
        return false;
    }


    int count = claim.amount;
    for(struct claim& oldClaim : std::vector<struct claim>({claims_.end()-1, claims_.begin()})){
        if(oldClaim.rank == claim.rank){
            count += oldClaim.amount;
        } else {
            break;
        }
    }
    // DISCARD_LIMIT amount of same claims
    if(count >= DISCARD_LIMIT){
        return true;
    }
    return false;

}

bool Game::isValidPlay(cards cards, int claim)
{
    if(not(0 < cards.size() && cards.size() <= DISCARD_LIMIT)){
        return false;
    }
    if(not claims_.empty()){
        if(claims_.back().rank == 2){
            if(cards.size() > 1){
                return false;
            }
        }
    }
    if(claim == 10 || claim == 14 || claim == 2){
        if(cards.size() > 1){
            handler_->print("You can't play 2, 10 or Ace when over 1 card is selected");
            return false;
        }
    }
    if(deckPlay_.played){
        if(not (*cards.begin() == deckPlay_.card) || cards.size() != 1){
            handler_->print("You can only play the card you picked up");
            return false;
        }
    }

    if(toDiscard()){
        return false;
    }


    return isValidClaim(claim);
}

bool Game::isValidClaim(int claim)
{
    // No last claim
    if(claims_.empty()){
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

    int lastClaim = claims_.back().rank;

    if(claim == 2){
        return true;
    }
    if(claim < lastClaim){
        handler_->print("Can't play rank that is less than already played");
        return false;
    }
    if(lastClaim == 2){
        handler_->print("Only 2 can be played on top of 2");
        return false;
    }
    if(claim == 10){
        if(lastClaim > 9){
            handler_->print("10 can only be played if last played is 9 or lower");
            return false;
        }
    }
    if(claim == 14){
        if(lastClaim < 11){
            handler_->print("Ace can only be played if last played is Jack or higher");
            return false;
        }
    }
    if(lastClaim < 7){
        if(11 <= claim && claim <= 13){
            handler_->print("Court cards can only be played if last played is 7 or higher");
            return false;
        }
    }
    return true;


}
