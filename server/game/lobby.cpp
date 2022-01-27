#include "lobby.h"
#include "../eventhandler.h"

Lobby::Lobby(EventHandler *eventHandler):
    eventHandler_(eventHandler),
    members_({})
{
    std::cout << "Created lobby " << this << std::endl;
}

Lobby::~Lobby()
{
    std::cout << "Deleted lobby " << this << std::endl;
}

void Lobby::setState(id member, bool state)
{
    if(not hasMember(member)){
        return;
    }
    members_.at(member) = state;
    if(isReady()){
        signalReady();
    }
}

bool Lobby::add(id member)
{
    if(not Group::add(member)){
        return false;
    }
    members_.insert({member, false});
    return true;
}

bool Lobby::isReady()
{
    for(auto& [member, ready] : members_){
        if(not ready){
            return false;
        }
    }
    return true;
}

void Lobby::signalReady()
{
    eventHandler_->start(this);
}

