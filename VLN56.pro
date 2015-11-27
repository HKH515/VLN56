QT += core
QT -= gui

TARGET = VLN56
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    data.cpp \
    person.cpp

HEADERS += \
    data.h \
    person.h

