#-------------------------------------------------
#
# Project created by QtCreator 2015-08-23T15:13:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuadTree
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nodo.cpp \
    quadtree.cpp

HEADERS  += mainwindow.h \
    nodo.h \
    quadtree.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
