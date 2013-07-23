TEMPLATE = lib

QT       += core

QT       -= gui

# Define library type
CONFIG += staticlib

HEADERS += \
    seaenvinput.h \
    readinputfile.h \
    hydrodynamicinput.h \
    forcesinput.h \
    datainput.h \
    controlinput.h \
    bodiesinput.h

SOURCES += \
    seaenvinput.cpp \
    readinputfile.cpp \
    hydrodynamicinput.cpp \
    forcesinput.cpp \
    datainput.cpp \
    controlinput.cpp \
    bodiesinput.cpp

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

#Add motion solver library
unix|win32: LIBS += -L$$OUT_PWD/../motion_solver/ -lmotion_solver

INCLUDEPATH += $$PWD/../motion_solver
DEPENDPATH += $$PWD/../motion_solver

win32: PRE_TARGETDEPS += $$OUT_PWD/../motion_solver/motion_solver.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../motion_solver/libmotion_solver.a

#Add global objects library
unix|win32: LIBS += -L$$OUT_PWD/../global_objects/ -lglobal_objects

INCLUDEPATH += $$PWD/../global_objects
DEPENDPATH += $$PWD/../global_objects

win32: PRE_TARGETDEPS += $$OUT_PWD/../global_objects/global_objects.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../global_objects/libglobal_objects.a

#Add wave calcs library
unix|win32: LIBS += -L$$OUT_PWD/../wave_calcs/ -lwave_calcs

INCLUDEPATH += $$PWD/../wave_calcs
DEPENDPATH += $$PWD/../wave_calcs

win32: PRE_TARGETDEPS += $$OUT_PWD/../wave_calcs/wave_calcs.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../wave_calcs/libwave_calcs.a
