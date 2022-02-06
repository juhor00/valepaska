#include "handcards.h"

HandCards::HandCards():
    CardCollection()
{

}

void HandCards::add(Card card)
{
    CardCollection::add(card);
}

void HandCards::add(cards cards)
{
    for(Card card : cards){
        add(card);
    }
}

void HandCards::remove(Card card)
{
    CardCollection::remove(card);
}

void HandCards::remove(cards cards)
{
    for(Card card : cards){
        remove(card);
    }
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

void HandCards::moveTo(CardCollection *other, cards cards)
{
    for(Card card : cards){
        CardCollection::moveTo(other, card);
    }
}

void HandCards::clear()
{
    CardCollection::clear();
}
