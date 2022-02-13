#ifndef TURNORDER_H
#define TURNORDER_H

#include "member.h"
#include "group.h"
#include <random>
#include <chrono>
#include <unordered_set>

struct Node {

    Member* member;
    Node* next;
};

class TurnException : public std::exception {
public:
    TurnException(std::string message):
        message_("TurnException: " + message){}

    TurnException():
        TurnException("Exception"){}

    virtual const char* what() const throw(){
        return message_.c_str();
    }

private:
    std::string message_;

};

class TurnOrder : public Group
{
public:
    TurnOrder();
    ~TurnOrder();

    virtual bool add(id id) override;
    virtual bool add(Member* member) override;
    virtual bool remove(id id) override;
    virtual bool remove(Member* member) override;
    Member* next();
    void shuffle();
    Member *getTurn();
    std::vector<Member*> getMembersInOrder();
    bool isInTurn(Member* member);
    bool isInTurn(id id);

    Member* turnTo(Member* member);
    Member* turnTo(id id);

protected:

    void addToOrder(Member* member);
    void removeFromOrder(Member* member);
    bool hasMemberInOrder(Member* member);

private:

    void deleteOrder();

    Node* turn_;
    std::unordered_set<Member*> order_;
};

#endif // TURNORDER_H
