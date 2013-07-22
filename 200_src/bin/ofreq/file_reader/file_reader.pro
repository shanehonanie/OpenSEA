TEMPLATE = lib

QT       += core

QT       -= gui

HEADERS += \
    seaenvinput.h \
    readinputfile.h \
    hydrodynamicinput.h \
    forcesinput.h \
    datainput.h \
    controlinput.h \
    bodiesinput.h \
    activeforcematrix.h

SOURCES += \
    seaenvinput.cpp \
    readinputfile.cpp \
    hydrodynamicinput.cpp \
    forcesinput.cpp \
    datainput.cpp \
    controlinput.cpp \
    bodiesinput.cpp \
    activeforcematrix.cpp

# Include header files path for libraries
INCLUDEPATH += \
    $$PWD/../../../lib \
    $$PWD/../motion_solver \
    $$PWD/../global_objects \
    $$PWD/../wave_calcs

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
