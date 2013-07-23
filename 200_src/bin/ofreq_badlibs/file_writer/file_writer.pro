TEMPLATE = lib

QT       += core

QT       -= gui

# Define library type
CONFIG += staticlib

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
    $$PWD/../../../var

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


# Include Derived Outputs Library
unix|win32: LIBS += -L$$OUT_PWD/../derived_outputs/ -lderived_outputs

INCLUDEPATH += $$PWD/../derived_outputs
DEPENDPATH += $$PWD/../derived_outputs

win32: PRE_TARGETDEPS += $$OUT_PWD/../derived_outputs/derived_outputs.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../derived_outputs/libderived_outputs.a
