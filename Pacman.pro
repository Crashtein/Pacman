#-------------------------------------------------
#
# Project created by QtCreator 2019-06-08T17:05:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pacman
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        game.cpp \
    main.cpp \
    gamemap.cpp \
    mapobject.cpp \
    movable.cpp \
    monster.cpp \
    pacman.cpp \
    block.cpp \
    coin.cpp

HEADERS += \
        game.h \
    gamemap.h \
    mapobject.h \
    movable.h \
    monster.h \
    pacman.h \
    block.h \
    coin.h

FORMS += \
        game.ui \
    gamemap.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    data.qrc
