#ifndef TESTER_H
#define TESTER_H

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

    void deckEvent(Card card) override;
    void print(std::string message) override;
    void pendingDiscard(discardID id) override;

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
        {"play", "Player in turn plays their cards"},
        {"deck", "Player in turn plays from deck"},
        {"suspect", "Suspect the latest played cards"}

    };
    const int cmdLen_;
    inline static const string BACK = "Go back by typing \"back\"";
    inline static const string RETURN = "Returning...";
};

#endif // TESTER_H
