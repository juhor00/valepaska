#ifndef CARD_H
#define CARD_H


#include <string>

class Card
{
public:
    Card(int rank, char suit);




    int rank() const;
    char suit() const;
    bool equals(const Card other) const;
    std::string toString() const;
    bool operator==(const Card other) const;
    bool operator<(const Card other) const;





private:

    int rank_;
    char suit_;

    static char rankToChar(int rank);

};

#endif // CARD_H
