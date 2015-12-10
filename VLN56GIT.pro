#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T12:18:43
#
#-------------------------------------------------

QT       += core gui
QT       += core sql

CONFIG += c++11
CONFIG -= x86_64

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VLN56GIT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    computer.cpp \
    computerRepository.cpp \
    connectionRepository.cpp \
    connections.cpp \
    data.cpp \
    display.cpp \
    domain.cpp \
    person.cpp \
    personRepository.cpp \
    presentation.cpp \
    utils.cpp \
    verifyinput.cpp

HEADERS  += mainwindow.h \
    computer.h \
    computerRepository.h \
    connectionRepository.h \
    connections.h \
    data.h \
    display.h \
    domain.h \
    person.h \
    personRepository.h \
    presentation.h \
    utils.h \
    verifyinput.h

FORMS    += mainwindow.ui

DISTFILES += \
    data.sqlite \
    VLN56GIT.pro.user \
    data.dat \
    splash.txt \
    README.md
