#include "eventhandler.h"

EventHandler::EventHandler():
    latestLobby_(new Lobby),
    clientsByLobby_({}),
    clients_({})
{
    clientsByLobby_.insert({latestLobby_, {}});
    acceptClients();
}

EventHandler::~EventHandler()
{
    for(auto& [lobby, clients] : clientsByLobby_){
        delete lobby;
    }
    if(latestLobby_ != nullptr){
        delete latestLobby_;
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
    clients_.insert(client);

    // Add to latest game's client list
    auto clients = getClientsByLobby(latestLobby_);
    clients.push_back(client);
    clientsByLobby_.at(latestLobby_) = clients;

    // Start game and create new
    if(clients.size() == LOBBY_SIZE_MAX){
        latestLobby_->start();
        createNewLobby();
    }
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
    Lobby* lobby = getLobbyByClient(client);
    std::vector<SOCKET> clients = getClientsByLobby(lobby);
    clients.erase(std::find(clients.begin(), clients.end(), client));
    clientsByLobby_.at(lobby) = clients;
    clients_.erase(client);

    if(clients.empty() and clientsByLobby_.size() > 1){
        clientsByLobby_.erase(lobby);
        delete lobby;
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

void EventHandler::createNewLobby()
{
    latestLobby_ = new Lobby();
    clientsByLobby_.insert({latestLobby_, {}});
}

Lobby *EventHandler::getLobbyByClient(SOCKET client)
{
    for(auto& [lobby, clients] : clientsByLobby_){
        // Game has client
        if(std::find(clients.begin(), clients.end(), client) != clients.end()){
            return lobby;
        }
    }
    return nullptr;
}

std::vector<SOCKET> EventHandler::getClientsByLobby(Lobby *lobby)
{
    return clientsByLobby_.at(lobby);
}

bool EventHandler::hasClient(SOCKET client)
{
    return std::find(clients_.begin(), clients_.end(), client) != clients_.end();
}
