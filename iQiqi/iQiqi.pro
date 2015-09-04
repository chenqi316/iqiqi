#-------------------------------------------------
#
# Project created by QtCreator 2015-08-29T16:05:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iQiqi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    iTunesHelper/CommonHelper.cpp \
    iTunesHelper/ConnectHelper.cpp \
    iTunesHelper/iOSConnect.cpp \
    iTunesHelper/iOSDevice.cpp \
    iTunesHelper/iTunesApi.cpp

HEADERS  += mainwindow.h \
    BaseDef.h \
    iTunesHelper/CommonHelper.h \
    iTunesHelper/ConnectHelper.h \
    iTunesHelper/iOSConnect.h \
    iTunesHelper/iOSDef.h \
    iTunesHelper/iOSDevice.h \
    iTunesHelper/iTunesApi.h

FORMS    += mainwindow.ui
