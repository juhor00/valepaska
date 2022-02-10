#ifndef GAME_H
#define GAME_H

#include "groups/turnorder.h"
#include "groups/player.h"
#include "cards/deck.h"
#include "cards/cardstack.h"

const int DRAW_MIN = 5;
const int DISCARD_LIMIT = 4;


class EventHandler;

class Game : public TurnOrder
{
public:
    Game(EventHandler* eventHandler);
    Game();
    ~Game();

    // Players
    bool add(id id) override;
    bool add(Member* member) override;
    Player* getPlayer(id id);
    std::vector<Player*> getPlayers();

    // Game
    void initGame();
    void print();

    void play(Player* player, cards cards, int claimRank);
    void play(id player, cards cards, int claimRank);

    void deckPlay(id player);
    void deckPlayClaim(int rank);

private:


    Player *changeTurn();

    // Deck
    void draw(Player* player);
    void draw(Player* player, int amount);
    void drawTo(Player* player, int target);
    Card playFromDeck(Player* player);

    // CardStack
    void takeLatest(Player* player);

    // Game
    bool isValidPlay(cards cards, int claim);
    bool isValidClaim(int claim);

    EventHandler* eventHandler_;
    Deck* deck_;
    CardStack* cardStack_;
    Player* inTurn_;
    int lastClaim_;
};

#endif // GAME_H
