#include "group.h"

Group::Group():
    members_({})
{

}

Group::~Group()
{

}

bool Group::add(id member)
{
    if(size() >= MAX_SIZE){
        return false;
    }
    if(not hasMember(member)){
        members_.push_back(member);
        return true;
    }
    return false;
}

bool Group::remove(id member)
{
    if(not hasMember(member)){
        return false;
    }
    members_.erase(std::find(members_.begin(), members_.end(), member));
    return true;
}

bool Group::hasMember(id member)
{
    return std::find(members_.begin(), members_.end(), member) != members_.end();
}

std::vector<id> Group::getMembers()
{
    return members_;
}

int Group::size()
{
    return members_.size();
}

bool Group::isFull()
{
    return size() >= MAX_SIZE;
}

bool Group::isEmpty()
{
    return size() == 0;
}

void Group::transferTo(Group *other)
{
    for(id member : members_){
        other->add(member);
    }
};

