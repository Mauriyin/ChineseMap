#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T00:36:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = map_sys
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    prov_info.cpp \
    help.cpp

HEADERS  += widget.h \
    prov_info.h \
    help.h

FORMS    += widget.ui \
    prov_info.ui \
    help.ui

RESOURCES += \
    pic_res.qrc
