TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../event.cpp \
        ../utilities.cpp \
        eventhandler.cpp \
        game/cards/card.cpp \
        game/cards/cardcollection.cpp \
        game/cards/cardstack.cpp \
        game/cards/deck.cpp \
        game/game.cpp \
        game/groups/group.cpp \
        game/groups/lobby.cpp \
        game/groups/member.cpp \
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
    game/game.h \
    game/groups/group.h \
    game/groups/lobby.h \
    game/groups/member.h \
    server.h

LIBS += -lws2_32
