CONFIG	     += console debug
QT	     += svg
HEADERS	     += aqp/alt_key.hpp \
    nodeitem.hpp \
    attachmentitem.h \
    nodewidget.h \
    nodewidgetproxy.h \
    xmdnodedata.h
SOURCES	     += aqp/alt_key.cpp \
    nodeitem.cpp \
    attachmentitem.cpp \
    nodewidget.cpp \
    nodewidgetproxy.cpp \
    xmdnodedata.cpp
HEADERS	     += aqp/kuhn_munkres.hpp
SOURCES	     += aqp/kuhn_munkres.cpp
HEADERS	     += aqp/aqp.hpp
SOURCES	     += aqp/aqp.cpp
INCLUDEPATH  += aqp
HEADERS	     += textedit/textedit.hpp
SOURCES	     += textedit/textedit.cpp
RESOURCES    += textedit/textedit.qrc
INCLUDEPATH  += textedit
HEADERS	     += global.hpp
SOURCES	     += global.cpp
HEADERS	     += swatch.hpp
SOURCES	     += swatch.cpp
HEADERS	     += itemtypes.hpp
HEADERS	     += boxitem.hpp
SOURCES	     += boxitem.cpp
HEADERS	     += smileyitem.hpp
SOURCES	     += smileyitem.cpp
HEADERS	     += textitem.hpp
SOURCES	     += textitem.cpp
HEADERS	     += textitemdialog.hpp
SOURCES	     += textitemdialog.cpp
HEADERS	     += transformwidget.hpp
SOURCES	     += transformwidget.cpp
HEADERS	     += brushwidget.hpp
SOURCES	     += brushwidget.cpp
HEADERS	     += penwidget.hpp
SOURCES	     += penwidget.cpp
HEADERS	     += graphicsview.hpp
HEADERS	     += mainwindow.hpp
SOURCES	     += mainwindow.cpp
SOURCES	     += main.cpp
RESOURCES    += pagedesigner.qrc
DEFINES	     += USE_STL
QT += widgets #added for Qt5
QT += printsupport
#DEFINES	     += ALTERNATIVE_RESIZING
win32 { INCLUDEPATH += . }

FORMS += \
    form.ui
