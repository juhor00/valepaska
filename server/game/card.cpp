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

std::string Card::toString() const
{
    return std::string({Card::rankToChar(rank()), suit()});
}

char Card::rankToChar(int rank)
{
    switch(rank){
    case 11:
        return 'J';
    case 12:
        return 'Q';
    case 13:
        return 'K';
    case 14:
        return 'A';
    default:
        return (char) rank;
    }
}
