#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "server.h"
#include "./game/lobby.h"
#include "./game/game.h"

class EventHandler;
typedef void (EventHandler::*handler)(SOCKET, parameters&);

class EventHandler : protected Server
{
public:
    EventHandler();
    ~EventHandler();

    void start(Lobby* lobby);

    // Event generators
    void generateTurnEvent(Game* game, id player);
    void generateWinEvent(Game* game, id player);
    void generateLoseEvent(Game* game, id player);
    void generateReadyEvent(Game* game, id player);

    void generatePlayEvent(Game* game, cards& cards);
    void generateDrawEvent(Game* game, cards& cards);

protected:

    bool handleEvent(Event& event) override;
    bool addClient(SOCKET client) override;
    bool removeClient(SOCKET client) override;

private:
    // Event handlers

    // Sending
    bool sendEvent(Event& event);
    void broadcast(Event& event);

    // Other event methods
    bool isHandler(command command);
    bool isGenerator(command command);

    // Lobby handling methods
    Lobby* createNewLobby();

    Game *toGame(Lobby* lobby);

    // Group handling methods
    Group *getGroupByClient(SOCKET client);
    std::vector<SOCKET> getClientsByGroup(Group* group);
    bool hasClient(SOCKET client);
    id changeForClient(SOCKET client, id player);


    Lobby* latestLobby_;
    std::unordered_map<Group*, std::vector<SOCKET>> clientsByGroup_;
    std::vector<SOCKET> clients_;

    std::unordered_map<command, handler> handlers_ = {
        {},
    };

    std::unordered_set<command> generators_ = {

    };
};

#endif // EVENTHANDLER_H
