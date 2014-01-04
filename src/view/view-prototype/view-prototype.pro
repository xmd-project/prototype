#-------------------------------------------------
#
# Project created by QtCreator 2014-01-03T17:38:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = view-prototype
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    node.cpp \
    edge.cpp \
    nodewidget.cpp

HEADERS  += mainwindow.h \
    scene.h \
    node.h \
    edge.h \
    nodewidget.h

FORMS    += mainwindow.ui \
    nodewidgetexample.ui
