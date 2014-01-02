QT	     += svg
HEADERS	     +=  \
    nodewidget.h \
    nodedata.h \
    nodeproxywidget.h
SOURCES	     +=  \
    nodewidget.cpp \
    nodedata.cpp \
    nodeproxywidget.cpp
HEADERS	     +=
HEADERS	     +=
SOURCES	     +=
SOURCES	     += main.cpp
RESOURCES    += nodetemplate.qrc
DEFINES	     += USE_STL
QT += widgets #added for Qt5
QT += printsupport
#DEFINES	     += ALTERNATIVE_RESIZING
#CONFIG	     += console debug
win32 { INCLUDEPATH += . }

FORMS += \
    form.ui
