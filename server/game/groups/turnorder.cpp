#include "turnorder.h"

TurnOrder::TurnOrder():
    turn_(nullptr),
    order_({})
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
    std::default_random_engine rng;
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(members.begin(), members.end(), rng);

    for(Member* member : members){
        addToOrder(member);
    }
}

Member *TurnOrder::getTurn()
{
    return turn_->member;
}

std::vector<Member *> TurnOrder::getMembersInOrder()
{
    std::vector<Member*> order({turn_->member});
    Node* iter = turn_->next;
    while(iter != turn_){
        order.push_back(iter->member);
        iter = iter->next;
    }
    return order;
}

bool TurnOrder::isInTurn(Member *member)
{
    return turn_->member == member;
}

bool TurnOrder::isInTurn(id id)
{
    return turn_->member->getId() == id;
}

Member *TurnOrder::turnTo(Member *member)
{
    if(not hasMemberInOrder(member)){
        throw TurnException("No member: " + std::to_string(member->getId()));
    }
    Member* iter = member;
    while(member != getTurn()){
        iter = next();
    }
    return iter;
}

Member *TurnOrder::turnTo(id id)
{
    Member* member = getMember(id);
    return turnTo(member);
}

void TurnOrder::addToOrder(Member *member)
{
    order_.insert(member);
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
    if(not hasMemberInOrder(member)){
        throw TurnException("No member : " + std::to_string(member->getId()));
    }
    order_.erase(member);
    Node* iter = turn_;

    // iter until iter->next is to be removed
    while(iter->next->member != member){
        iter = iter->next;
    }

    Node* after = iter->next->next;

    // if member to remove is in turn, change to next
    if(member == turn_->member){
        turn_ = after;
    }

    delete iter->next;
    iter->next = after;
}

bool TurnOrder::hasMemberInOrder(Member *member)
{
    return order_.find(member) != order_.end();
}

void TurnOrder::deleteOrder()
{
    Node* iter = turn_->next;
    Node* previous = turn_;
    previous->next = nullptr;
    delete previous;

    while(iter != turn_){
        previous = iter;
        iter = iter->next;
        delete previous;
    }
    turn_ = nullptr;
}
