#ifndef TESTER_H
#define TESTER_H

#include "game/game.h"
#include "handler.h"
#include "../utilities.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;


class BackException : public exception {
public:

    BackException(const exception& e):
        exception(e){}
    BackException():
        exception(){}
};

class Tester : public Handler
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

    id promptPlayer();
    cards promptCards(id player);
    int promptClaim();



    Game* game_;
    map<string, string> help_ = {
        {"?", "Prints all commands and their description"},
        {"quit", "Quits the program"},
        {"print", "Prints the game state"},
        {"play", "Prompts for the player and cards to be played"},
        {"deck", "Prompts for the player to play from deck"},

    };
    const int cmdLen_;
    inline static const string BACK = "Go back by typing \"back\"";
};

#endif // TESTER_H
