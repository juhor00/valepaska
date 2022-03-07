QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../card.cpp \
    ../event.cpp \
    ../utilities.cpp \
    client.cpp \
    eventhandler.cpp \
    gui/widgets/aspectratio.cpp \
    gui/widgets/layouts/cardlayout.cpp \
    gui/widgets/layouts/cardstack.cpp \
    gui/widgets/layouts/hand.cpp \
    gui/widgets/cards/cardwidget.cpp \
    gui/widgets/cards/closedcard.cpp \
    gui/widgets/cards/openedcard.cpp \
    main.cpp \
    gui/mainwindow.cpp

HEADERS += \
    ../card.h \
    ../event.h \
    ../utilities.h \
    client.h \
    eventhandler.h \
    gui/widgets/aspectratio.h \
    gui/widgets/layouts/cardlayout.h \
    gui/widgets/layouts/cardstack.h \
    gui/widgets/layouts/hand.h \
    gui/mainwindow.h \
    gui/widgets/cards/cardwidget.h \
    gui/widgets/cards/closedcard.h \
    gui/widgets/cards/openedcard.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    networkConfig.txt

LIBS += -lws2_32

RESOURCES += \
    gui/resources.qrc
