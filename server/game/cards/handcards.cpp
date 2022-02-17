#include "handcards.h"

HandCards::HandCards():
    CardCollection()
{

}

bool HandCards::add(Card card)
{
    return CardCollection::add(card);
}

bool HandCards::add(cards cards)
{
    for(Card card : cards){
        if(not add(card)){
            return false;
        }
    }
    return true;
}

bool HandCards::remove(Card card)
{
    return CardCollection::remove(card);
}

bool HandCards::remove(cards cards)
{
    for(Card card : cards){
        if(not remove(card)){
            return false;
        }
    }
    return true;
}

bool HandCards::hasCards(cards cards)
{
    for(Card card : cards){
        if(not CardCollection::hasCard(card)){
            return false;
        }
    }
    return true;
}

void HandCards::clear()
{
    CardCollection::clear();
}
