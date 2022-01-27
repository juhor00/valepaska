#include "eventhandler.h"

EventHandler::EventHandler():
    latestLobby_(new Lobby(this)),
    groups_({latestLobby_})
{
    acceptClients();
}

EventHandler::~EventHandler()
{
    for(Group* group : groups_){
        delete group;
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

    // Add to latest game's client list
    latestLobby_->add(client);

    if(latestLobby_->isFull()){
        createNewLobby();
    }
    return true;

}

bool EventHandler::removeClient(SOCKET client)
{
    if(not Server::removeClient(client)){
        return false;
    }

    // Find list of clients of the game where client is
    Group* group = getGroupByClient(client);
    group->remove(client);


    if(group->isEmpty() and groups_.size() > 1){
        groups_.erase(group);
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
    groups_.insert(latestLobby_);
    return latestLobby_;
}

Game *EventHandler::toGame(Lobby* lobby)
{
    Game* game = new Game(this);

    // Move clients from Lobby to Game
    lobby->transferTo(game);

    groups_.erase(lobby);
    groups_.insert(game);
    return game;
}

Group *EventHandler::getGroupByClient(SOCKET client)
{
    for(Group* group : groups_){
        // Game has client
        if(group->hasMember(client)){
            return group;
        }
    }
    return nullptr;
}
