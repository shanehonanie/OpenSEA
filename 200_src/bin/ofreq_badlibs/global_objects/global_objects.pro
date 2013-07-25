#-------------------------------------------------
#
# Project created by QtCreator 2013-07-21T14:46:31
#
#-------------------------------------------------

TEMPLATE = lib

QT       += core

QT       -= gui

# Define library type
CONFIG += staticlib

HEADERS += \
    wavefrequencies.h \
    wavedirections.h \
    system.h

SOURCES += \
    wavefrequencies.cpp \
    wavedirections.cpp \
    system.cpp \
    ofreq.cpp

# Include header files path for libraries
INCLUDEPATH += \
    $$PWD/../../../lib

# Platform Specific files go in these scope brackets
# ========================================================
win32 {
    # Any files specific to windows go in these brackets.

}

unix {
    # Any files specific to unix go in these brackets.

}
