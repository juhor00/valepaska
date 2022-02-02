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

bool CardCollection::hasCard(const Card card)
{
    return std::find_if(cards_.begin(), cards_.end(),
                 [card](const Card other){return card.equals(other);
                }) != cards_.end();
}

bool CardCollection::isEmpty()
{
    return cards_.empty();
}

void CardCollection::add(Card card)
{
    cards_.push_back(card);
}

Card CardCollection::getLast()
{
    return cards_.back();
}

Card CardCollection::getFirst()
{
    return cards_.front();
}
