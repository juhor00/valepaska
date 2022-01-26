#include "eventhandler.h"

EventHandler::EventHandler():
    latestLobby_(new Lobby(this)),
    clientsByGroup_({}),
    clients_({})
{
    clientsByGroup_.insert({latestLobby_, {}});
    acceptClients();
}

EventHandler::~EventHandler()
{
    for(auto& [lobby, clients] : clientsByGroup_){
        delete lobby;
    }
    if(latestLobby_ != nullptr){
        delete latestLobby_;
    }
}

void EventHandler::start(Lobby *lobby)
{
    if(lobby->size() > 1){
        toGame(lobby);
    }
}

bool EventHandler::handleEvent(Event &event)
{
    event.print();
    SOCKET client = event.getClient();
    command command = event.getCommand();
    parameters parameters = event.getParameters();

    if(not isHandler(command)){
        return false;
    }

    // Handle normally
    handler handler = handlers_.at(command);
    (this->*handler)(client, parameters);
    return true;
}

bool EventHandler::addClient(SOCKET client)
{
    if(!Server::addClient(client)){
        return false;
    }
    clients_.push_back(client);

    // Add to latest game's client list
    auto clients = getClientsByGroup(latestLobby_);
    clients.push_back(client);
    clientsByGroup_.at(latestLobby_) = clients;
    return true;

}

bool EventHandler::removeClient(SOCKET client)
{
    if(not Server::removeClient(client)){
        return false;
    }
    if(not hasClient(client)){
        return false;
    }

    // Find list of clients of the game where client is
    Group* group = getGroupByClient(client);
    std::vector<SOCKET> clients = getClientsByGroup(group);
    clients.erase(std::find(clients.begin(), clients.end(), client));
    clientsByGroup_.at(group) = clients;
    clients_.erase(std::find(clients_.begin(), clients_.end(), client));

    if(clients.empty() and clientsByGroup_.size() > 1){
        clientsByGroup_.erase(group);
        delete group;
    }
    return true;
}

bool EventHandler::sendEvent(Event &event)
{
    command command = event.getCommand();
    if(not isGenerator(command)){
        return false;
    }
    parameters parameters = event.getParameters();
    SOCKET client = event.getClient();
    message msg = command + " " + utils::join(parameters);
    sendToClient(client, msg);
    return true;
}

void EventHandler::broadcast(Event &event)
{
    std::cout << "Broadcasting" << std::endl;
    for(auto client : clients_){
        event.setClient(client);
        sendEvent(event);
    }
}

bool EventHandler::isHandler(command command)
{
    return handlers_.find(command) != handlers_.end();
}

bool EventHandler::isGenerator(command command)
{
    return generators_.find(command) != generators_.end();
}

Lobby* EventHandler::createNewLobby()
{
    latestLobby_ = new Lobby(this);
    clientsByGroup_.insert({latestLobby_, {}});
    return latestLobby_;
}

Game *EventHandler::toGame(Lobby* lobby)
{
    Game* game = new Game(this);
    lobby->transferTo(game);

    // Move clients from Lobby to Game
    std::vector<SOCKET> clients = clientsByGroup_.at(lobby);
    clientsByGroup_.erase(lobby);
    clientsByGroup_.insert({game, clients});
    return game;
}

Group *EventHandler::getGroupByClient(SOCKET client)
{
    for(auto& [group, clients] : clientsByGroup_){
        // Game has client
        if(std::find(clients.begin(), clients.end(), client) != clients.end()){
            return group;
        }
    }
    return nullptr;
}

std::vector<SOCKET> EventHandler::getClientsByGroup(Group *group)
{
    return clientsByGroup_.at(group);
}

bool EventHandler::hasClient(SOCKET client)
{
    return std::find(clients_.begin(), clients_.end(), client) != clients_.end();
}

id EventHandler::changeForClient(SOCKET client, id player)
{
    int clientIndex = std::find(clients_.begin(), clients_.end(), client) - clients_.begin();
    return player - (clientIndex < player ? 1 : 0);
}
