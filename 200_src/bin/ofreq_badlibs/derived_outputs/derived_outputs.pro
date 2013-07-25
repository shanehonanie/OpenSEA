TEMPLATE = lib

QT += core

QT -= gui

# Define library type
CONFIG += staticlib

HEADERS += \
    outputslist.h \
    outputsbody.h \
    outputderived.h \
    globalvelocity.h \
    globalsolution.h \
    globalmotion.h \
    globalacceleration.h

SOURCES += \
    outputslist.cpp \
    outputsbody.cpp \
    outputderived.cpp \
    globalvelocity.cpp \
    globalsolution.cpp \
    globalmotion.cpp \
    globalacceleration.cpp

# Include header files path for libraries
INCLUDEPATH += \
    $$PWD/../../../lib \

# force rebuild if the headers change
DEPENDPATH += $${INCLUDEPATH}

# Platform Specific files go in these scope brackets
# ========================================================
win32 {
    # Any files specific to windows go in these brackets.
    LIBS += \
        $$PWD/../../../lib/armadillo.h
}

unix {
    # Any files specific to unix go in these brackets.
    LIBS += -larmadillo #Libs for unix filesystem
}

# Add in library for motion model
unix|win32: LIBS += -L$$OUT_PWD/../motion_model/ -lmotion_model

INCLUDEPATH += $$PWD/../motion_model
DEPENDPATH += $$PWD/../motion_model

win32: PRE_TARGETDEPS += $$OUT_PWD/../motion_model/motion_model.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../motion_model/libmotion_model.a
