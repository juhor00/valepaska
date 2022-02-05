#include "cardstack.h"

CardStack::CardStack():
    CardCollection(),
    latestCards_({})
{

}

void CardStack::add(Card card)
{
    CardCollection::add(card);
    latestCards_ = {card};
}

void CardStack::add(std::vector<Card> cards)
{
    for(Card card : cards){
        this->add(card);
    }
    latestCards_ = cards;
}

void CardStack::clear()
{
    CardCollection::clear();
}

std::vector<Card> CardStack::getLatest()
{
    return latestCards_;
}
