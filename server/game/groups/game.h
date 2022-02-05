#ifndef GAME_H
#define GAME_H

#include "group.h"


class EventHandler;

class Game : public Group
{
public:
    Game(EventHandler* eventHandler);

private:

    EventHandler* eventHandler_;
};

#endif // GAME_H
