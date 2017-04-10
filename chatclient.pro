QT += core gui widgets

INCLUDEPATH += ./include

TARGET = chat
TEMPLATE = app

SOURCES += src/main.cpp\
           src/chatwindow.cpp\
           src/chatpanel.cpp \
           src/Packet.cpp \
           src/RaftNode.cpp \

HEADERS += include/chatwindow.h\
           include/chatpanel.h \
           include/Packet.h \
           include/RaftNode.h \
