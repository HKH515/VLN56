QT += core
QT -= gui

TARGET = VLN56
CONFIG += console
CONFIG -= app_bundle

CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    data.cpp \
    person.cpp \
    presentation.cpp \
	domain.cpp

HEADERS += \
    data.h \
    presentation.h \
    person.h \
	domain.h

DISTFILES += \
    splash.txt \
    data.dat

