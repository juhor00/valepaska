TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../card.cpp \
        ../event.cpp \
        ../utilities.cpp \
        eventhandler.cpp \
        game/cards/cardcollection.cpp \
        game/cards/cardstack.cpp \
        game/cards/deck.cpp \
        game/cards/handcards.cpp \
        game/game.cpp \
        game/groups/group.cpp \
        game/groups/lobby.cpp \
        game/groups/member.cpp \
        game/groups/player.cpp \
        game/groups/turnorder.cpp \
        main.cpp \
        server.cpp \
        tester.cpp

HEADERS += \
    ../card.h \
    ../event.h \
    ../utilities.h \
    eventhandler.h \
    game/cards/cardcollection.h \
    game/cards/cardstack.h \
    game/cards/deck.h \
    game/cards/handcards.h \
    game/game.h \
    game/groups/group.h \
    game/groups/lobby.h \
    game/groups/member.h \
    game/groups/player.h \
    game/groups/turnorder.h \
    handler.h \
    server.h \
    tester.h

LIBS += -lws2_32
