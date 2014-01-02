QT += widgets

HEADERS	    =   mainwindow.h \
		diagramitem.h \
		diagramscene.h \
		arrow.h \
		diagramtextitem.h \
    nodeproxywidget.h \
    nodewidget.h
SOURCES	    =   mainwindow.cpp \
		diagramitem.cpp \
		main.cpp \
		arrow.cpp \
		diagramtextitem.cpp \
		diagramscene.cpp \
    nodeproxywidget.cpp \
    nodewidget.cpp
RESOURCES   =	diagramscene.qrc


# install
target.path = .
INSTALLS += target

simulator: warning(This example might not fully work on Simulator platform)

FORMS += \
    nodewidget.ui
