QT += core sql
QT -= gui
QT += core sql

TARGET = VLN56
CONFIG += console
CONFIG -= app_bundle

CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    data.cpp \
    person.cpp \
    presentation.cpp \
	domain.cpp \
    computer.cpp \
    verifyinput.cpp

HEADERS += \
    data.h \
    presentation.h \
    person.h \
	domain.h \
    computer.h \
    verifyinput.h

DISTFILES += \
    splash.txt \
    data.dat

