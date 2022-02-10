#include "cardstack.h"

CardStack::CardStack():
    CardCollection(),
    latestCards_({})
{

}

void CardStack::add(Card card)
{
    add(cards({card}));
}

void CardStack::add(cards cards)
{
    for(Card card : cards){
        CardCollection::add(card);
    }
    latestCards_ = cards;
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
