#ifndef TESTER_H
#define TESTER_H

#include "game/game.h"
#include "eventhandler.h"
#include <iostream>

using namespace std;

class Tester
{
public:
    Tester();
    ~Tester();

private:

    void mainloop();
    int promptPlayers();

    Game* game_;
};

#endif // TESTER_H
