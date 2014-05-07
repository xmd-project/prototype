#-------------------------------------------------
#
# Project created by QtCreator 2014-01-31T19:31:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = view-prototype-2
TEMPLATE = app


SOURCES += main.cpp\
        xmainwindow.cpp \
    xscene.cpp \
    xgraphicsview.cpp \
    xrect.cpp \
    xpainterconstant.cpp \
    zoomwidget.cpp \
    xgroup.cpp \
    xmd.cpp

HEADERS  += xmainwindow.h \
    xscene.h \
    xgraphicsview.h \
    xrect.h \
    xpainterconstant.h \
    zoomwidget.h \
    xgroup.h \
    xmd.h

FORMS    += \
    zoomwidget.ui

RESOURCES += \
    view_prototype.qrc
