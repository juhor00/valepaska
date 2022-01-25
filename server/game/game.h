#ifndef GAME_H
#define GAME_H

#include <unordered_set>

class Card;

using player = int;
using cards = std::unordered_set<Card>;

class Game
{
public:
    Game();
};

#endif // GAME_H
