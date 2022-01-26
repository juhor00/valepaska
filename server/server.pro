TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../event.cpp \
        ../utilities.cpp \
        eventhandler.cpp \
        game/game.cpp \
        game/group.cpp \
        game/lobby.cpp \
        main.cpp \
        server.cpp

HEADERS += \
    ../event.h \
    ../utilities.h \
    eventhandler.h \
    game/game.h \
    game/group.h \
    game/lobby.h \
    server.h

LIBS += -lws2_32
