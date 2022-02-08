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
        getline(cin, input);

        if(input == "?"){
            printHelp();
        } else if(input == "quit"){
            return;
        } else if(input == "print"){
            game_->print();
        } else if(input == "play"){
            try{
                id player = promptPlayer();
                cards cards = promptCards(player);
                game_->play(player, cards, promptClaim());
            }
            catch(BackException&){
                cout << "Returning..." << endl;
            }


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
        getline(cin, input);
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

id Tester::promptPlayer()
{
    string input;
    auto players = game_->getPlayers();
    sort(players.begin(), players.end(), [](Player* a, Player* b){return a->getId() < b->getId();});

    while(true){
        cout << BACK << endl;
        cout << "Select a player " << players.front()->getId() << " - " << players.back()->getId() << ": > ";
        getline(cin, input);
        try{
            if(input == "back"){
                throw BackException();
            }
            id player = (id) stoi(input);
            if(find_if(players.begin(), players.end(), [player](Player* other){return other->getId() == player;}) != players.end()){
                return player;
            } else {
                cout << "Invalid player" << endl;
            }
        }
        catch(std::invalid_argument& e){
            cout << "Input must be number" << endl;
        }
    }
}

cards Tester::promptCards(id id)
{
    cout << "Player " << id << " cards:" << endl;
    Player* player = game_->getPlayer(id);
    player->print();
    string input;

    while(true){
        cout << BACK << endl;
        cout << "Choose cards separated by : > ";

        getline(cin, input);
        if(input == "back"){
            throw BackException();
        }
        auto cardsStr = utils::split(input, " ");
        vector<Card> cards;
        for(string& card : cardsStr){
            cout << card << endl;
            try{
                cards.push_back(Card(utils::toUpper(card)));
            }
            catch(InvalidCardException& e){
                cout << e.what() << endl;
                break;
            }
        }

        if(cards.empty()){
            continue;
        }

        for(Card card : cards){
            cout << card.toString() << endl;
        }
        if(player->hasCards(cards)){
            return cards;
        } else {
            cout << "Invalid cards" << endl;
        }

    }

}

int Tester::promptClaim()
{

    string input;


    while(true){
        cout << BACK << endl;
        cout << "Choose claim (2-14): > ";
        getline(cin, input);
        try{
            if(input == "back"){
                throw BackException();
            }
            int rank = stoi(input);
            if(2 <= rank && rank <= 14){
                return rank;
            } else {
                cout << "Invalid claim" << endl;
            }

        }
        catch(std::invalid_argument& e){
            cout << "Claim must be number" << endl;
        }
    }
}
