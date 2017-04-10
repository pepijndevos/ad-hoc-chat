QT += core gui widgets

INCLUDEPATH += ./include

TARGET = chat
TEMPLATE = app

SOURCES += src/main.cpp\
           src/chatwindow.cpp\
           src/chatpanel.cpp

HEADERS += include/chatwindow.h\
           include/chatpanel.h
