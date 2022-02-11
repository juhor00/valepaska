#include "cardstack.h"

CardStack::CardStack():
    CardCollection(),
    latestCards_({})
{

}

bool CardStack::add(Card card)
{
    return add(cards({card}));
}

bool CardStack::add(cards cards)
{
    for(Card card : cards){
        if(not CardCollection::add(card)){
            return false;
        }
    }
    latestCards_ = cards;
    return true;
}

void CardStack::clear()
{
    CardCollection::clear();
}

cards CardStack::getLatest()
{
    return latestCards_;
}

cards CardStack::getAll()
{
    cards cards = CardCollection::getAll();
    clear();
    return cards;
}
