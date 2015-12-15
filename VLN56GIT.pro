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
    person.cpp \
    personRepository.cpp \
    utils.cpp \
    personsservice.cpp \
    computerservice.cpp \
    connectionsservice.cpp \
    add_computers.cpp \
    add_connections.cpp \
    add_persons.cpp

HEADERS  += mainwindow.h \
    computer.h \
    computerRepository.h \
    connectionRepository.h \
    person.h \
    personRepository.h \
    utils.h \
    computerservice.h \
    connectionsservice.h \
    personsservice.h \
    add_computers.h \
    add_connections.h \
    add_persons.h

FORMS    += mainwindow.ui \
            add_persons.ui \
            add_computers.ui \
    add_connections.ui


DISTFILES += \
    data.sqlite \
    VLN56GIT.pro.user \
    data.dat \
    splash.txt \
    README.md

OTHER_FILES += \
    images/computer.ico

RESOURCES += \
    resources.qrc
