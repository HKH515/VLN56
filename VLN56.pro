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
	compareperson.cpp \
    computer.cpp

HEADERS += \
    data.h \
    presentation.h \
    person.h \
	domain.h \
	compareperson.h \
    computer.h

DISTFILES += \
    splash.txt \
    data.dat

