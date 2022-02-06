#include "tester.h"

Tester::Tester():
    game_(new Game)
{
    promptPlayers();
}

Tester::~Tester()
{
    delete game_;
}

void Tester::mainloop()
{
    while(true){

    }
}

int Tester::promptPlayers()
{
    string amount;
    while(true){
        cout << "How many players? >";
        cin >> amount;
        try{
            return stoi(amount);
        }
        catch(std::invalid_argument e){
            cout << "Invalid number" << endl;
        }
    }
}
