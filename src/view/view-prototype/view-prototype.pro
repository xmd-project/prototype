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
    nodewidget.cpp \
    nodedata.cpp

HEADERS  += mainwindow.h \
    scene.h \
    node.h \
    edge.h \
    nodewidget.h \
    nodedata.h

FORMS    += mainwindow.ui \
    nodewidgetexample.ui \
    form.ui

RESOURCES += \
    nodetemplate.qrc

OTHER_FILES += \
    images/align-bottom.png \
    images/zoom-out.png \
    images/zoom-in.png \
    images/weblink.png \
    images/solidlinestyle.png \
    images/smileysmile.png \
    images/smileysad.png \
    images/smileyneutral.png \
    images/showgrid.png \
    images/pen.png \
    images/nodeproxy.png \
    images/icon.png \
    images/filesave.png \
    images/filequit.png \
    images/fileprint.png \
    images/fileopen.png \
    images/filenew.png \
    images/fileexport.png \
    images/editselecteditem.png \
    images/editpaste.png \
    images/editcut.png \
    images/editcopy.png \
    images/editcleartransforms.png \
    images/editaddtext.png \
    images/editaddstar.png \
    images/editaddsmiley.png \
    images/editaddpolynomial.png \
    images/editaddnode.png \
    images/editaddimage.png \
    images/editaddbox.png \
    images/dottedlinestyle.png \
    images/dashedlinestyle.png \
    images/color.png \
    images/brush.png \
    images/attachment.png \
    images/align-top.png \
    images/align-right.png \
    images/align-left.png
