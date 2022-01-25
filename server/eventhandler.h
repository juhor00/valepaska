#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "server.h"

class Lobby;
class EventHandler;
typedef void (EventHandler::*handler)(SOCKET, parameters&);

class EventHandler : protected Server
{
public:
    EventHandler();
    ~EventHandler();

    // Event generators

protected:

    virtual bool handleEvent(Event& event) override;
    virtual bool addClient(SOCKET client) override;
    virtual bool removeClient(SOCKET client) override;

private:
    // Event handlers

    // Sending
    bool sendEvent(Event& event);
    void broadcast(Event& event);

    // Other event methods
    bool isHandler(command command);
    bool isGenerator(command command);


    Lobby* latestLobby_;
    std::unordered_map<Lobby*, std::vector<SOCKET>> clientsByLobby_;
    std::unordered_set<SOCKET> clients_;

    std::unordered_map<command, handler> handlers_ = {
        {},
    };

    std::unordered_set<command> generators_ = {

    };
};

#endif // EVENTHANDLER_H
