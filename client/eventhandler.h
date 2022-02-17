#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include "../event.h"
#include "client.h"


class EventHandler;
typedef void (EventHandler::*handler)(parameters&);
typedef void (EventHandler::*generator)(parameters&);

class MainWindow;

class EventHandler : public Client
{
public:

    EventHandler(MainWindow* m);
    ~EventHandler();

protected:

    // General event handlers
    void noConnectionEvent() override;
    bool handleEvent(Event& event) override;




private:

    bool sendEvent(Event& event);
    bool isHandler(command& command);
    bool isGenerator(command& command);

    Client* server;
    std::string address_;
    std::string port_;
    MainWindow* mainWindow;

    std::unordered_set<command> generators = {};
    std::unordered_map<command, handler> handlers = {};
};

#endif // EVENTHANDLER_H
