#ifndef TURNORDER_H
#define TURNORDER_H

#include "member.h"
#include "group.h"
#include <random>

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

private:

    void addToOrder(Member* member);
    void removeFromOrder(Member* member);
    void deleteOrder();

    Node* first_;
};

#endif // TURNORDER_H