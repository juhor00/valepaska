TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../event.cpp \
        ../utilities.cpp \
        eventhandler.cpp \
        game/card.cpp \
        game/cardcollection.cpp \
        game/deck.cpp \
        game/game.cpp \
        game/group.cpp \
        game/lobby.cpp \
        main.cpp \
        server.cpp

HEADERS += \
    ../event.h \
    ../utilities.h \
    eventhandler.h \
    game/card.h \
    game/cardcollection.h \
    game/deck.h \
    game/game.h \
    game/group.h \
    game/lobby.h \
    server.h

LIBS += -lws2_32
