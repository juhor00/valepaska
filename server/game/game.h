#ifndef GAME_H
#define GAME_H

#include "groups/turnorder.h"
#include "groups/player.h"
#include "cards/deck.h"
#include "cards/cardstack.h"


class EventHandler;

class Game : public TurnOrder
{
public:
    Game(EventHandler* eventHandler);
    ~Game();

    // Players
    bool add(id id) override;
    bool add(Member* member) override;
    Player* getPlayer(id id);
    std::vector<Player*> getPlayers();
    Player *changeTurn();

    // Game
    void initGame();

    // Deck
    void draw(Player* player);
    void draw(Player* player, int amount);
    Card playFromDeck(Player* player);

    // CardStack
    void takeLatest(Player* player);

private:

    EventHandler* eventHandler_;
    Deck* deck_;
    CardStack* cardStack_;
    Player* inTurn;
};

#endif // GAME_H
