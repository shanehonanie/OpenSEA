#-------------------------------------------------
#
# Project created by QtCreator 2013-07-21T14:46:31
#
#-------------------------------------------------

TEMPLATE = app

QT       += core

QT       -= gui

TARGET = ofreq
CONFIG   += console
CONFIG   -= app_bundle

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

linux {
    # Any files specific to linux go in these brackets.

}
