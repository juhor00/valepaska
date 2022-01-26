#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "server.h"
#include "./game/lobby.h"

class EventHandler;
typedef void (EventHandler::*handler)(SOCKET, parameters&);

class EventHandler : protected Server
{
public:
    EventHandler();
    ~EventHandler();

    // Event generators
    void generateTurnEvent(Lobby* lobby, player player);
    void generateWinEvent(Lobby* lobby, player player);
    void generateLoseEvent(Lobby* lobby, player player);
    void generateReadyEvent(Lobby* lobby, player player);

    void generatePlayEvent(Lobby* lobby, cards& cards);
    void generateDrawEvent(Lobby* lobby, cards& cards);

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

    // Lobby handling methods
    void createNewLobby();
    Lobby *getLobbyByClient(SOCKET client);
    std::vector<SOCKET> getClientsByLobby(Lobby* lobby);
    bool hasClient(SOCKET client);
    player changeForClient(SOCKET client, player player);


    Lobby* latestLobby_;
    std::unordered_map<Lobby*, std::vector<SOCKET>> clientsByLobby_;
    std::vector<SOCKET> clients_;

    std::unordered_map<command, handler> handlers_ = {
        {},
    };

    std::unordered_set<command> generators_ = {

    };
};

#endif // EVENTHANDLER_H
