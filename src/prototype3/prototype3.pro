#-------------------------------------------------
#
# Project created by QtCreator 2014-05-29T15:19:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prototype3
TEMPLATE = app


SOURCES += main.cpp\
        xmainwindow.cpp \
    xview.cpp \
    xnotebrowser.cpp \
    xzoomwidget.cpp \
    xscene.cpp \
    xdragdropwindow.cpp \
    xnodedata.cpp \
    xdatabase.cpp

HEADERS  += xmainwindow.h \
    xview.h \
    xnotebrowser.h \
    xzoomwidget.h \
    xscene.h \
    xdragdropwindow.h \
    xnodedata.h \
    xdatabase.h

FORMS    += xmainwindow.ui \
    xzoomwidget.ui \
    xdragdropwindow.ui
