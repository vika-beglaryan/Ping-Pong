#-------------------------------------------------
#
# Project created by QtCreator 2018-03-03T14:31:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Pong
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    pads.cpp \
    ball.cpp \
    startwidget.cpp \
    options.cpp \
    rules.cpp

HEADERS  += widget.h \
    pads.h \
    ball.h \
    startwidget.h \
    options.h \
    rules.h

FORMS    += widget.ui

OTHER_FILES +=

DISTFILES +=

RESOURCES += \
    resources.qrc
