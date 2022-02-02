#include "card.h"



Card::Card(int rank, char suit) : rank_(rank),
    suit_(suit)
{}

int Card::rank() const
{
    return rank_;
}

char Card::suit() const
{
    return suit_;
}

bool Card::equals(const Card other) const
{
    return rank() == other.rank() && suit() == other.suit();
}
