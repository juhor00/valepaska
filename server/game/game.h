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

    bool add(id id) override;
    bool add(Member* member) override;
    Player* getPlayer(id id);

private:

    EventHandler* eventHandler_;
    Deck* deck_;
    CardStack* cardStack_;
};

#endif // GAME_H
