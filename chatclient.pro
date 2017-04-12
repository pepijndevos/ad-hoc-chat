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
           src/Message.pb.cc \
           src/RaftMessage.pb.cc \
           src/Security.cpp \
           src/Message.cpp \
#    src/RaftNode.cpp \
#    src/Routing.cpp \

HEADERS += include/chatwindow.h \
           include/chatpanel.h \
           include/transceiver.h \
           include/router.h \
           include/Packet.pb.h \
           include/Message.pb.h \
           include/RaftMessage.pb.h \
           include/Security.h \
           include/md5.h \
           include/Message.h \
#           include/RaftNode.h \
#    include/Routing.h \

DISTFILES += \
    Message.proto \
    Packet.proto \
    ChatMessage.proto
