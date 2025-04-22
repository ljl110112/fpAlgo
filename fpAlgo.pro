#-------------------------------------------------
#
# Project created by QtCreator 2025-04-22T10:17:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fpAlgo
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    algotask.cpp \
    dataclass.cpp

HEADERS  += mainwindow.h \
    algotask.h \
    dataclass.h

FORMS    += mainwindow.ui
