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
    person.cpp \
    utils.cpp \
    personsservice.cpp \
    computerservice.cpp \
    connectionsservice.cpp \
    verification.cpp \
    addcomputers.cpp \
    addpersons.cpp \
    addconnections.cpp \
    computerrepository.cpp \
    connectionrepository.cpp \
    personrepository.cpp

HEADERS  += mainwindow.h \
    computer.h \
    person.h \
    utils.h \
    computerservice.h \
    verification.h \
    connectionsservice.h \
    connectionrepository.h \
    computerrepository.h \
    personrepository.h \
    personsservice.h \
    addcomputers.h \
    addpersons.h \
    addconnections.h

FORMS    += mainwindow.ui \
    addcomputers.ui \
    addpersons.ui \
    addconnections.ui


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
