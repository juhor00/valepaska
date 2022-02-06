#include "tester.h"

Tester::Tester():
    game_(new Game)
{
    createPlayers(promptPlayers());
    cout << "Elossa ollaa" << endl;
    mainloop();
}

Tester::~Tester()
{
    delete game_;
}

void Tester::mainloop()
{
    string input;
    while(true){
        cout << "Enter command (type '?' for help) > ";
        cin >> input;

        if(input == "?"){
            printHelp();
        } else if(input == "quit"){
            return;
        }

    }
}

int Tester::promptPlayers()
{
    string input;
    while(true){
        cout << "How many players? > ";
        cin >> input;
        try{
            int amount = stoi(input);
            if(1 < amount && amount < 6){
                return amount;
            } else {
                cout << "Number must be between 2-5" << endl;
            }
        }
        catch(std::invalid_argument& e){
            cout << "Invalid number" << endl;
        }
    }
}

void Tester::createPlayers(int amount)
{
    for(int i=0; i<amount; i++){
        game_->add(i);
    }
}

void Tester::printHelp()
{
    cout << "----HELP----" << endl;
    cout << "Command | Description" << endl;
    for(auto& [command, desc] : help_){
       cout << command << " | " << desc << endl;
    }
    cout << "----HELP----" << endl;

}
