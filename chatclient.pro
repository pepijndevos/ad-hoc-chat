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

# Copy the ad-hoc setup/desetup scripts
isEmpty(TARGET_EXT) {
    win32 {
        TARGET_CUSTOM_EXT = .exe
        SUBDIR = ""
    }
    unix {
        SUBDIR = ""
        TARGET_CUSTOM_EXT = ""
    }
    macx {
        TARGET_CUSTOM_EXT = .app
        SUBDIR = /Contents/MacOS
    }
} else {
    TARGET_CUSTOM_EXT = $${TARGET_EXT}
    SUBDIR = ""
}

DEPLOY_TARGET = $${OUT_PWD}/$${TARGET}$${TARGET_CUSTOM_EXT}$${SUBDIR}

#SCRIPT.commands =
QMAKE_POST_LINK += $${QMAKE_COPY} $$shell_quote($$shell_path($${PWD}/adhoc_scripts/adhoc_desetup)) $$shell_quote($$shell_path($${DEPLOY_TARGET}/adhoc_desetup)) &&
QMAKE_POST_LINK += $${QMAKE_COPY} $$shell_quote($$shell_path($${PWD}/adhoc_scripts/adhoc_setup)) $$shell_quote($$shell_path($${DEPLOY_TARGET}/adhoc_setup)) &&
QMAKE_POST_LINK += $${QMAKE_COPY} $$shell_quote($$shell_path($${PWD}/adhoc_scripts/adhoc_remove.bat)) $$shell_quote($$shell_path($${DEPLOY_TARGET}/adhoc_remove.bat)) &&
QMAKE_POST_LINK += $${QMAKE_COPY} $$shell_quote($$shell_path($${PWD}/adhoc_scripts/adhoc_leave.bat)) $$shell_quote($$shell_path($${DEPLOY_TARGET}/adhoc_leave.bat)) &&
QMAKE_POST_LINK += $${QMAKE_COPY} $$shell_quote($$shell_path($${PWD}/adhoc_scripts/adhoc_join.bat)) $$shell_quote($$shell_path($${DEPLOY_TARGET}/adhoc_join.bat))
