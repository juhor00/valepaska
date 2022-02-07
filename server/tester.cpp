#include "tester.h"

Tester::Tester():
    game_(new Game),
    cmdLen_(calcLongestCmd())
{
    createPlayers(promptPlayers());
    game_->initGame();
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
        } else if(input == "print"){
            game_->print();
        } else {
            cout << "Invalid command" << endl;
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
    int cmdLen = max(cmdLen_, (int) size("Command"));
    cout << "----HELP----" << endl;
    cout << setw(cmdLen) << "Command" << " | " << "Description" << endl;
    for(auto& [command, desc] : help_){
       cout << setw(cmdLen) << command << " | " << desc << endl;
    }
    cout << "----HELP----" << endl;

}

int Tester::calcLongestCmd()
{
    auto iter = std::max_element(help_.begin(), help_.end(),
                                 [](auto a, auto b){return size(a.first) < size(b.first);});
    return size(iter->first);

}
