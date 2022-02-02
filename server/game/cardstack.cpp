#include "cardstack.h"

CardStack::CardStack():
    CardCollection()
{

}

void CardStack::add(Card card)
{
    CardCollection::add(card);
}

void CardStack::add(std::vector<Card> cards)
{
    for(Card card : cards){
        this->add(card);
    }
}

void CardStack::clear()
{
    CardCollection::clear();
}
