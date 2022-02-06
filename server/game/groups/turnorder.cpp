#include "turnorder.h"

TurnOrder::TurnOrder()
{

}

TurnOrder::~TurnOrder()
{
    deleteOrder();
}

bool TurnOrder::add(id id)
{
    if(not Group::add(id)){
        return false;
    }
    addToOrder(getMember(id));
    return true;
}

bool TurnOrder::remove(id id)
{
    if(not Group::hasMember(id)){
        return false;
    }
    Node* iter = first_;
    Member* member = getMember(id);

    // iter until iter->next is to be removed
    while(iter->next->member != member){
        iter = iter->next;
    }

    Node* after = iter->next->next;
    delete iter->next;
    iter->next = after;
    return Group::remove(id);
}

Member* TurnOrder::next()
{
    first_ = first_->next;
    return getTurn();
}

void TurnOrder::shuffle()
{
    deleteOrder();

    std::vector<Member*> members = Group::getMembers();
    auto rng = std::default_random_engine {};
    std::shuffle(members.begin(), members.end(), rng);

    for(Member* member : members){
        addToOrder(member);
    }
}

Member *TurnOrder::getTurn()
{
    return first_->member;
}

void TurnOrder::addToOrder(Member *member)
{
    Node* iter = first_;
    while(iter->next != first_){
        iter = iter->next;
    }
    iter->next = new Node({member, first_});
}

void TurnOrder::deleteOrder()
{
    Node* previous = first_;
    Node* iter = first_->next;

    while(iter != nullptr){
        delete previous;
        previous = iter;
        iter = iter->next;
    }
    delete previous;
    first_ = nullptr;
}
