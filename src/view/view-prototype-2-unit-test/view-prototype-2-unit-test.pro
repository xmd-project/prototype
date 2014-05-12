#-------------------------------------------------
#
# Project created by QtCreator 2014-05-12T22:31:05
#
#-------------------------------------------------

QT       += testlib

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tst_xgraphicsitem
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_xgraphicsitem.cpp \
    ../view-prototype-2/xmd.cpp \
    ../view-prototype-2/xgraphicsview.cpp \
    ../view-prototype-2/xgroup.cpp \
    ../view-prototype-2/xmainwindow.cpp \
    ../view-prototype-2/xpainterconstant.cpp \
    ../view-prototype-2/xrect.cpp \
    ../view-prototype-2/xscene.cpp \
    ../view-prototype-2/zoomwidget.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../view-prototype-2/xmd.h \
    ../view-prototype-2/xgraphicsview.h \
    ../view-prototype-2/xgroup.h \
    ../view-prototype-2/xmainwindow.h \
    ../view-prototype-2/xpainterconstant.h \
    ../view-prototype-2/xrect.h \
    ../view-prototype-2/xscene.h \
    ../view-prototype-2/zoomwidget.h

RESOURCES += \
    ../view-prototype-2/view_prototype.qrc

FORMS += \
    ../view-prototype-2/zoomwidget.ui
