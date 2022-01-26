#ifndef GAME_H
#define GAME_H

#include "group.h"
#include <unordered_set>

class Card;
class EventHandler;

using cards = std::unordered_set<Card>;

class Game : public Group
{
public:
    Game(EventHandler* eventHandler);

private:

    EventHandler* eventHandler_;
};

#endif // GAME_H
