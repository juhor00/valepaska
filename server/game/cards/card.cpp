#include "card.h"



Card::Card(int rank, char suit)
{
    if(not(2 <= rank && rank <= 14)){
        throw InvalidCardException("Invalid rank " + std::to_string(rank));
    }

    std::string a = "CDSH";
    if(a.find(suit) == a.npos){
        throw InvalidCardException("Invalid suit " + std::string(1, suit));
    }

    rank_ = rank;
    suit_ = suit;
}

Card::Card(std::string str):
    Card(getRankFromStr(str), getSuitFromStr(str)){}

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

bool Card::operator==(const Card other) const
{
    return equals(other);
}

bool Card::operator<(const Card other) const
{
    return rank() < other.rank();
}

int Card::getRankFromStr(std::string s)
{
    if(s.empty()){
        throw InvalidCardException();
    }
    char rankC = s.at(0);
    int rank;
    switch(rankC){
    case 'T':
        rank = 10;
        break;
    case 'J':
        rank = 11;
        break;
    case 'Q':
        rank = 12;
        break;
    case 'K':
        rank = 13;
        break;
    case 'A':
        rank = 14;
        break;
    default:
        rank = std::atoi(&rankC);
    }
    return rank;
}

char Card::getSuitFromStr(std::string s)
{
    if(s.size() < 2){
        throw InvalidCardException();
    }
    return s.at(1);
}

char Card::rankToChar(int rank)
{
    switch(rank){
    case 10:
        return 'T';
    case 11:
        return 'J';
    case 12:
        return 'Q';
    case 13:
        return 'K';
    case 14:
        return 'A';
    default:
        return '0' + rank;
    }
}
