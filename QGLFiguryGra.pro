#-------------------------------------------------
#
# Project created by QtCreator 2014-04-17T17:39:25
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS +=
TARGET = QGLFigury
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myglwidget.cpp\
figura.cpp\
kolo.cpp\
kwadrat.cpp\
trojkat.cpp \
    poziomy.cpp \
    odcinek.cpp

HEADERS  += mainwindow.h \
myglwidget.h\
figura.h\
kolo.h\
kwadrat.h\
trojkat.h \
    poziomy.h \
    odcinek.h

FORMS    += mainwindow.ui
