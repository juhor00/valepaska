#ifndef LOBBY_H
#define LOBBY_H

#include "group.h"
#include <unordered_map>
#include <iostream>

class EventHandler;


class Lobby : public Group
{
public:
    Lobby(EventHandler* eventHandler);
     ~Lobby();
    void setState(id member, bool isReady);
    bool add(id member) override;

private:

    bool isReady();
    void signalReady();

    EventHandler* eventHandler_;
    std::unordered_map<id, bool> members_;
};

#endif // LOBBY_H
