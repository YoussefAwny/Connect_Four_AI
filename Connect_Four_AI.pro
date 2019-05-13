#-------------------------------------------------
#
# Project created by QtCreator 2019-05-09T15:36:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Connect_Four_AI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    game.h \
    player.h

FORMS    += mainwindow.ui
