TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../event.cpp \
        main.cpp \
        server.cpp

HEADERS += \
    ../event.h \
    server.h
