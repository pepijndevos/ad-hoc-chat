QT += core gui widgets

INCLUDEPATH += ./include

TARGET = chat
TEMPLATE = app

SOURCES += src/main.cpp\
           src/chatwindow.cpp \
    src/adhoc.cpp \
    src/utils.cpp \
    src/Packet.cpp

HEADERS += include/chatwindow.h \
    include/adhoc.h \
    include/utils.h \
    include/Packet.h
