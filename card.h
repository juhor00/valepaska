#ifndef CARD_H
#define CARD_H


#include <string>

class InvalidCardException : public std::exception {
public:
    InvalidCardException():
        InvalidCardException("Invalid card"){}

    InvalidCardException(const std::string message):
        message_("InvalidCardException: " + message){}

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
    std::string toString() const;
    bool operator==(const Card other) const;
    bool operator<(const Card other) const;


    static bool isValidRank(int rank);
    static bool isValidSuit(char suit);

protected:

    static int getRankFromStr(std::string s);
    static char getSuitFromStr(std::string s);

private:

    int rank_;
    char suit_;

    static char rankToChar(int rank);

};

template<> struct std::hash<Card> {
    std::size_t operator()(const Card& c) const noexcept{
        std::size_t h1 = std::hash<int>{}(c.rank());
        std::size_t h2 = std::hash<char>{}(c.suit());
        return h1 ^ (h2 << 1);
    }
};

#endif // CARD_H
