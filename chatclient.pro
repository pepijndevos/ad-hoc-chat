QT += core gui widgets network

CONFIG += c++11

# External Libs
INCLUDEPATH += "$${PWD}/extern_libs/include"
LIBS += -L"$${PWD}/extern_libs/lib" -lprotobuf

INCLUDEPATH += ./include

TARGET = chat
TEMPLATE = app

SOURCES += src/main.cpp\
           src/chatwindow.cpp \
           src/chatpanel.cpp \
           src/transceiver.cpp \
           src/router.cpp \
           src/Packet.pb.cc \
           src/ChatMessage.pb.cc \
           src/Message.cpp \
           src/Message.pb.cc \
           src/Security.cpp \
#    src/RaftNode.cpp \
#    src/Routing.cpp \

HEADERS += include/chatwindow.h \
           include/chatpanel.h \
           include/transceiver.h \
           include/router.h \
           include/Packet.pb.h \
           include/ChatMessage.pb.h \
           include/Message.h \
           include/Message.pb.h \
           include/Security.h \
           include/md5.h \
#           include/RaftNode.h \
#    include/Routing.h \

DISTFILES += \
    Message.proto \
    Packet.proto \
    ChatMessage.proto
