#ifndef GAME_H
#define GAME_H

#include "groups/turnorder.h"
#include "groups/player.h"
#include "cards/deck.h"
#include "cards/cardstack.h"

const int DRAW_MIN = 5;
const int DISCARD_LIMIT = 4;

struct deckPlay {
    Card card;
    bool played;
};

struct claim {
    int rank;
    Player* claimer;
};


class Handler;

class Game : public TurnOrder
{
public:
    Game(Handler* handler);
    ~Game();

    // Players
    bool add(id id) override;
    bool add(Member* member) override;
    Player* getPlayer(id id);
    std::vector<Player*> getPlayers();

    // Game
    void initGame();
    void print();

    bool play(id player, cards cards, int claimRank);
    bool play(Player* player, cards cards, int claimRank);

    void deckPlay(id player);
    void deckPlay(Player* player);

    bool suspect(id player);
    bool suspect(Player* player);

private:

    // Deck
    void draw(Player* player);
    void draw(Player* player, int amount);
    void drawTo(Player* player, int target);
    Card playFromDeck(Player* player);

    // CardStack
    void takeAll(Player* player);

    // Game
    bool isValidPlay(cards cards, int claim);
    bool isValidClaim(int claim);

    Handler* handler_;
    Deck* deck_;
    CardStack* cardStack_;
    struct claim claim_;
    struct deckPlay deckPlay_;
};

#endif // GAME_H
