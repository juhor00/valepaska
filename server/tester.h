#ifndef TESTER_H
#define TESTER_H

#include "game/game.h"
#include "eventhandler.h"
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

class Tester
{
public:
    Tester();
    ~Tester();

private:

    void mainloop();
    int promptPlayers();
    void createPlayers(int amount);
    void printHelp();
    int calcLongestCmd();

    Game* game_;
    map<string, string> help_ = {
        {"?", "Prints all commands and their description"},
        {"quit", "Quits the program"},
        {"print", "Prints the game state"},
    };
    const int cmdLen_;
};

#endif // TESTER_H
