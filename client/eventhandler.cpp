#include "eventhandler.h"
#include "./gui/mainwindow.h"


EventHandler::EventHandler(MainWindow* m):
    mainWindow(m)
{


}

EventHandler::~EventHandler()
{

}





void EventHandler::noConnectionEvent()
{

}

bool EventHandler::handleEvent(Event &event)
{
    event.print();
    command command = event.getCommand();
    if(not isHandler(command)){
        return false;
    }
    parameters parameters = event.getParameters();
    handler handler = handlers.at(command);
    (this->*handler)(parameters);

    return true;
}



bool EventHandler::sendEvent(Event &event)
{
    command command = event.getCommand();
    if(not isGenerator(command)){
        return false;
    }
    parameters parameters = event.getParameters();
    message msg = command + " " + utils::join(parameters);
    server->sendToServer(msg);
    return true;
}

bool EventHandler::isHandler(command &command)
{
    return handlers.find(command) != handlers.end();
}

bool EventHandler::isGenerator(command &command)
{
    return generators.find(command) != generators.end();
}

