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
        game/cards/card.cpp \
        game/cards/cardcollection.cpp \
        game/cards/cardstack.cpp \
        game/cards/deck.cpp \
        game/cardstack.cpp \
        game/deck.cpp \
        game/game.cpp \
        game/group.cpp \
        game/groups/game.cpp \
        game/groups/group.cpp \
        game/groups/lobby.cpp \
        game/lobby.cpp \
        main.cpp \
        server.cpp

HEADERS += \
    ../event.h \
    ../utilities.h \
    eventhandler.h \
    game/cards/card.h \
    game/cards/cardcollection.h \
    game/cards/cardstack.h \
    game/cards/deck.h \
    game/groups/game.h \
    game/groups/group.h \
    game/groups/lobby.h \
    server.h

LIBS += -lws2_32
