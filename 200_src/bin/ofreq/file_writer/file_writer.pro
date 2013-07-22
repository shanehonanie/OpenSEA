TEMPLATE = lib

QT       += core

QT       -= gui

HEADERS += \
    filewriter.h \
    filewavefrequencies.h \
    filewavedirections.h \
    filelist.h

SOURCES += \
    filewriter.cpp \
    filewavefrequencies.cpp \
    filewavedirections.cpp \
    filelist.cpp

# Include header files path for libraries
INCLUDEPATH += \
    $$PWD/../../../lib \
    $$PWD/../../../var \
    $$PWD/../derived_outputs

OTHER_FILES += \
    ../../../var/openseaheader.txt

# Platform Specific files go in these scope brackets
# ========================================================
win32 {
    # Any files specific to windows go in these brackets.
    LIBS += boost_system boost_filesystem
}

linux {
    # Any files specific to linux go in these brackets.
    LIBS += -lboost_system -lboost_filesystem   #Libs for linux filesystem
}

