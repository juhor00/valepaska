#ifndef TURNORDER_H
#define TURNORDER_H

#include "member.h"
#include "group.h"
#include <random>
#include <chrono>

struct Node {

    Member* member;
    Node* next;
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

private:

    void addToOrder(Member* member);
    void removeFromOrder(Member* member);
    void deleteOrder();

    Node* turn_;
};

#endif // TURNORDER_H
