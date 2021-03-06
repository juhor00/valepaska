#include "event.h"

Event::Event(message message):
    Event(INVALID_SOCKET, message){}

Event::Event(SOCKET client, message message):
    client_(client)
{
    auto i = message.find(" ");
    cmd_ = message.substr(0, i);

    // Parameters
    if(i != message.npos){
        message.erase(0, i+1);
        params_ = utils::split(message);
    } else {
        params_ = {};
        return;
    }
}

Event::Event(SOCKET client, command command, parameters parameters):
    client_(client), cmd_(command), params_(parameters)
{
}

void Event::setClient(SOCKET client)
{
    client_ = client;
}

std::string Event::getCommand()
{
    return cmd_;
}

std::vector<std::string> Event::getParameters()
{
    return params_;
}

SOCKET Event::getClient()
{
    return client_;
}

void Event::print()
{
    std::cout << "\tEVENT INFO" << std::endl;

    std::cout << "\t* Client: ";
    if(client_!=INVALID_SOCKET){std::cout << client_;} else {std::cout << "NULL";};
    std::cout << std::endl;

    std::cout << "\t* Command: " << cmd_ << std::endl;
    std::cout << "\t* Parameters: [ ";
    for(std::string& param : params_){
        std::cout << param << " ";
    }
    std::cout << "]" << std::endl;
}
