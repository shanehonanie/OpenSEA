TEMPLATE = lib

QT       += core

QT       -= gui

# Define library type
CONFIG += staticlib

HEADERS += \
    motionmodel.h \
    equationofmotion_01.h \
    equationofmotion.h

SOURCES += \
    motionmodel.cpp \
    equationofmotion_01.cpp \
    equationofmotion.cpp

# Include header files path for libraries
INCLUDEPATH += \
    $$PWD/../../../lib

# Platform Specific files go in these scope brackets
# ========================================================
win32 {
    # Any files specific to windows go in these brackets.
    LIBS += \
        $$PWD/../../../lib/armadillo.h
}

linux {
    # Any files specific to linux go in these brackets.
    LIBS += -larmadillo #Libs for linux filesystem
}



# Add motion solver library
unix|win32: LIBS += -L$$OUT_PWD/../motion_solver/ -lmotion_solver

INCLUDEPATH += $$PWD/../motion_solver
DEPENDPATH += $$PWD/../motion_solver

win32: PRE_TARGETDEPS += $$OUT_PWD/../motion_solver/motion_solver.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../motion_solver/libmotion_solver.a
