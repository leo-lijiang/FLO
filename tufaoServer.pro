######################################################################
# Automatically generated by qmake (3.0) ?? 4? 18 19:34:03 2017
######################################################################

TEMPLATE = app
TARGET = tufaoServer
INCLUDEPATH += .

# Input
HEADERS += App.h \
           cJSON.h \
           ClientsInfo.h \
           DBConnPool.h \
           dealmsg.h \
           Def.h \
           MsgMng.h \
           Player.h \
           Room.h
SOURCES += App.cpp \
           cJSON.c \
           ClientsInfo.cpp \
           DBConnPool.cpp \
           dealmsg.cpp \
           main.cpp \
           MsgMng.c \
           Player.cpp \
           Room.cpp
LIBS += -ltufao1
QT += core network sql

CONFIG += c++11