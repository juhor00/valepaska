#ifndef GAME_H
#define GAME_H

#include "groups/turnorder.h"
#include "groups/player.h"


class EventHandler;

class Game : public TurnOrder
{
public:
    Game(EventHandler* eventHandler);

    bool add(id id) override;
    bool add(Member* member) override;
    Player* getPlayer(id id);

private:

    EventHandler* eventHandler_;
};

#endif // GAME_H
