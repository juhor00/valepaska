#ifndef CARD_H
#define CARD_H


#include <string>


class InvalidCardException : public std::exception {
public:
    InvalidCardException():
        message_("Invalid card"){}

    InvalidCardException(const std::string message):
        message_(message){}

    virtual const char* what() const throw(){
        return message_.c_str();
    }


private:

    const std::string message_;
};


class Card
{
public:
    Card(int rank, char suit);
    Card(std::string str);




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
