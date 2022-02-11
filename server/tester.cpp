#include "tester.h"

Tester::Tester():
    game_(new Game(this)),
    cmdLen_(calcLongestCmd())
{
    //createPlayers(promptPlayers());
    createPlayers(4);
    game_->initGame();
    mainloop();
}

Tester::~Tester()
{
    delete game_;
}

void Tester::deckEvent(Card card)
{
    string input;
    bool played = false;
    do {
        cout << "You picked up " << card.toString() << " from deck" << endl;
        played = game_->play(game_->getTurn()->getId(), {card}, promptClaim());
    }  while(not played);

}

void Tester::print(string message)
{
    std::cout << message << std::endl;
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
            id player = game_->getTurn()->getId();
            try{
                cards cards = promptCards(player);
                game_->play(player, cards, promptClaim());
            }
            catch(BackException&){
                cout << RETURN << endl;
            }

        } else if(input == "deck"){
            id player = game_->getTurn()->getId();
            try{
                game_->deckPlay(player);
            }
            catch(BackException&){
                cout << RETURN << endl;
                cout << "You must play the drawn card!" << endl;
            }
        } else if(input == "suspect"){
            try{
                id player;
                bool suspected = false;
                do {
                    cout << "Who suspects?" << endl;
                    player = promptPlayer();
                    suspected = game_->suspect(player);
                } while(not suspected);
            }
            catch(BackException&){
                cout << RETURN << endl;
            }

        }else {
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

    cout << BACK << endl;

    while(true){

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
    Player* player = game_->getPlayer(id);
    player->print();
    string input;

    cout << BACK << endl;

    while(true){

        cout << "Choose cards separated by space: > ";

        getline(cin, input);

        cout << "Input: " << input << endl;

        if(input == "back"){
            throw BackException();
        }
        cards playedCards = {};
        std::vector<string> cardsStr = utils::split(input);
        for(string cardStr : cardsStr){
            cout << "splitted: " << cardStr << endl;
            cardStr = utils::toUpper(cardStr);
            cout << "toUpper: " << cardStr << endl;
            try{
                Card card(cardStr);
                playedCards.insert(card);
            }
            catch(InvalidCardException& e){
                cout << e.what() << endl;
                break;
            }
        }

        if(cardsStr.size() != playedCards.size()){
            // Not all succeeded
            continue;
        }

        if(playedCards.empty()){
            continue;
        }

        if(player->hasCards(playedCards)){
            return playedCards;
        } else {
            cout << "Player doesn't have all the cards!" << endl;
        }

    }

}

int Tester::promptClaim()
{

    string input;
    cout << BACK << endl;

    while(true){

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
