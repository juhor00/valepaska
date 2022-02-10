#include "cardcollection.h"
#include <algorithm>


CardCollection::CardCollection():
    cards_({})
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

void CardCollection::moveTo(CardCollection *other, Card card)
{
    other->add(card);
    remove(card);
}

void CardCollection::moveAllTo(CardCollection *other)
{
    for(Card card : cards_){
            moveTo(other, card);
        }
}

void CardCollection::add(const Card card)
{
    cards_.push_back(card);
}

void CardCollection::remove(const Card card)
{
    if(hasCard(card)){
        cards_.erase(std::find(cards_.begin(), cards_.end(), card));
    }
}

Card CardCollection::getLast()
{
    return cards_.back();
}

Card CardCollection::getFirst()
{
    return cards_.front();
}

void CardCollection::clear()
{
    cards_.clear();
}

cards CardCollection::getAll()
{
    return cards_;
}

cards::iterator CardCollection::begin()
{
    return cards_.begin();
}

cards::iterator CardCollection::end()
{
    return cards_.end();
}
