QT += core gui widgets

CONFIG += c++11

INCLUDEPATH += ./include

TARGET = chat
TEMPLATE = app

SOURCES += src/main.cpp\
           src/chatwindow.cpp \
           src/chatpanel.cpp \
    src/utils.cpp \
    src/Packet.cpp \
    src/RaftNode.cpp \
    src/Routing.cpp \
    src/Security.cpp

HEADERS += include/chatwindow.h \
           include/chatpanel.h \
    include/utils.h \
    include/Packet.h \
    include/RaftNode.h \
    include/Routing.h \
    include/Security.h
