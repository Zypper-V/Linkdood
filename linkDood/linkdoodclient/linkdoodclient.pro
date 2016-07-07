include(../syberos.pri)

TEMPLATE = lib
TARGET = linkdoodclient

QT       += dbus
QT       -= gui
CONFIG += c++11
DEFINES += EIMCLIENT_LIBRARY

#DEFINES += QT_NO_WARNING_OUTPUT  QT_NO_DEBUG_OUTPUT

SOURCES += \
    linkdoodclient.cpp \
    linkdoodtypes.cpp \
    common.cpp

HEADERS +=\
    linkdoodclient.h \
    linkdoodclient_global.h \
    linkdoodconst.h \
    linkdoodtypes.h \
    linkdoodtypedef.h \
    common.h

target.path = $$INSTALL_DIR/libs/

INSTALLS += target

