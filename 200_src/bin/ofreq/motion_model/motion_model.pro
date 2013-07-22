TEMPLATE = lib

QT       += core

QT       -= gui

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
    $$PWD/../../../lib \
    $$PWD/../motion_solver \
    $$PWD/../motion_model

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
