#include "turnorder.h"

TurnOrder::TurnOrder():
    turn_(nullptr)
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

bool TurnOrder::add(Member *member)
{
    if(not Group::add(member)){
        return false;
    }
    addToOrder(member);
    return true;
}

bool TurnOrder::remove(id id)
{
    if(not Group::hasMember(id)){
        return false;
    }
    removeFromOrder(Group::getMember(id));
    return Group::remove(id);
}

bool TurnOrder::remove(Member *member)
{
    if(not Group::hasMember(member)){
        return false;
    }
    removeFromOrder(member);
    return Group::remove(member);
}

Member* TurnOrder::next()
{
    turn_ = turn_->next;
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
    return turn_->member;
}

void TurnOrder::addToOrder(Member *member)
{
    if(turn_ == nullptr){
        turn_ = new Node({member, nullptr});
        turn_->next = turn_;
        return;
    }
    Node* iter = turn_;
    while(iter->next != turn_){
        iter = iter->next;
    }
    iter->next = new Node({member, turn_});
}

void TurnOrder::removeFromOrder(Member *member)
{
    Node* iter = turn_;

    // iter until iter->next is to be removed
    while(iter->next->member != member){
        iter = iter->next;
    }

    Node* after = iter->next->next;
    delete iter->next;
    iter->next = after;
}

void TurnOrder::deleteOrder()
{
    Node* previous = turn_;
    Node* iter = turn_->next;

    while(iter != nullptr){
        delete previous;
        previous = iter;
        iter = iter->next;
    }
    delete previous;
    turn_ = nullptr;
}
