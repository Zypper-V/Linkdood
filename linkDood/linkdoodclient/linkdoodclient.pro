include(../syberos.pri)

TEMPLATE = lib
TARGET = linkdoodclient

QT       += dbus
QT       -= gui
DEFINES += EIMCLIENT_LIBRARY

#DEFINES += QT_NO_WARNING_OUTPUT  QT_NO_DEBUG_OUTPUT

SOURCES += \
    linkdoodclient.cpp

HEADERS +=\
    linkdoodclient.h \
    linkdoodclient_global.h \
    linkdoodconst.h

target.path = $$INSTALL_DIR/libs/

INSTALLS += target

