#ifndef GAME_H
#define GAME_H

#include "groups/group.h"
#include "groups/player.h"


class EventHandler;

class Game : public Group
{
public:
    Game(EventHandler* eventHandler);

    bool add(id id) override;
    Player* getPlayer(id id);

private:

    EventHandler* eventHandler_;
};

#endif // GAME_H
