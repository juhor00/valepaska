#include "cardcollection.h"
#include <algorithm>


CardCollection::CardCollection():
    cards_({})
{

}

CardCollection::~CardCollection()
{

}

int CardCollection::size()
{
    return cards_.size();
}

bool CardCollection::hasCard(const Card card) const
{
    return std::find_if(cards_.begin(), cards_.end(),
                 [card](const Card other){return card == other;
                }) != cards_.end();
}

bool CardCollection::isEmpty()
{
    return cards_.empty();
}

void CardCollection::print()
{
    std::cout << "Cards [" << size() << "]:" << std::endl;
    for(Card card : cards_){
        std::cout << " * " << card.toString() << std::endl;
    }
}

bool CardCollection::add(const Card card)
{
    return cards_.insert(card).second;
}

bool CardCollection::remove(const Card card)
{
    if(hasCard(card)){
        cards_.erase(card);
        return true;
    }
    return false;
}

void CardCollection::clear()
{
    cards_.clear();
}

cards CardCollection::getAll()
{
    return cards_;
}
