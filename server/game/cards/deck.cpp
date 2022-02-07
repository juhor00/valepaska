#include "deck.h"



Deck::Deck():
    CardCollection()
{

}

Card Deck::getTop()
{
    Card last = getLast();
    remove(last);
    return last;
}

void Deck::generateFull()
{
    char suit;
    int rank;
    for(int i=0; i<DECK_SIZE; i++){
        if(i < DECK_SIZE * 1/4){
            suit = 'C';
        } else if(i < DECK_SIZE * 2/4){
            suit = 'D';
        } else if(i < DECK_SIZE * 3/4){
            suit = 'H';
        } else {
            suit = 'S';
        }
        rank = i % 13 + 2;
        this->add(Card(rank, suit));
    }
}

void Deck::shuffle()
{
    std::default_random_engine rng;
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(begin(), end(), rng);
}
