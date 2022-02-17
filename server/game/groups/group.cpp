#include "group.h"

Group::Group():
    members_({})
{

}

Group::~Group()
{
    for(auto& [id, member] : members_){
        delete member;
    }
}

bool Group::add(id id)
{
    if(size() >= MAX_SIZE){
        return false;
    }
    if(not hasMember(id)){
        members_.insert({id, new Member(id)});
        return true;
    }
    return false;
}

bool Group::remove(id id)
{
    if(not hasMember(id)){
        return false;
    }
    delete getMember(id);
    members_.erase(id);
    return true;
}

bool Group::hasMember(id id)
{
    return members_.find(id) != members_.end();
}

std::vector<id> Group::getIds()
{
    std::vector<id> ids = {};
    for(auto& [id, member] : members_){
        ids.push_back(id);
    }
    return ids;
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
    for(auto& [id, member] : members_){
        other->add(member->getId());
    }
}

bool Group::add(Member *member)
{
    if(hasMember(member)){
        return false;
    }
    members_.insert({member->getId(), member});
    return true;
}

bool Group::remove(Member *member)
{
    if(not hasMember(member)){
        return false;
    }
    members_.erase(member->getId());
    delete member;
    return true;
}

bool Group::hasMember(Member *member)
{
    for(auto& [id, other] : members_){
        if(member == other){
            return true;
        }
    }
    return false;
}

Member *Group::getMember(id id)
{
    return members_.at(id);
}

std::vector<Member *> Group::getMembers()
{
    std::vector<Member*> members = {};
    for(auto& [id, member] : members_){
        members.push_back(member);
    }
    return members;
};

