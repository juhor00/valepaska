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





private:

    int rank_;
    char suit_;

};

#endif // CARD_H
