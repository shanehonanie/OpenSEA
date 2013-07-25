TEMPLATE = lib

QT       += core

QT       -= gui

# Define library type
CONFIG += staticlib

HEADERS += \
    wavespreadmodel.h \
    wavespectrummodel.h \
    seaenviroment.h

SOURCES += \
    wavespreadmodel.cpp \
    wavespectrummodel.cpp \
    seaenviroment.cpp

# Include header files path for libraries
INCLUDEPATH += \
    $$PWD/../../../lib

# Platform Specific files go in these scope brackets
# ========================================================
win32 {
    # Any files specific to windows go in these brackets.
    LIBS += $$PWD/../../../lib/armadillo
}

unix {
    # Any files specific to unix go in these brackets.
    LIBS += -larmadillo #Libs for unix filesystem
}
