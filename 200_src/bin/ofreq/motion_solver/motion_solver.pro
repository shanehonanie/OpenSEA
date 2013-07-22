TEMPLATE = lib

QT       += core

QT       -= gui

HEADERS += \
    userforces.h \
    reactiveforcematrix.h \
    motionsolver.h \
    forcereactive.h \
    forceequation.h \
    forcederivative.h \
    forcecrossbody.h \
    forceactive.h \
    force.h \
    bodywithsolution.h \
    bodywithforcematrix.h \
    body.h

SOURCES += \
    userforces.cpp \
    reactiveforcematrix.cpp \
    motionsolver.cpp \
    forcereactive.cpp \
    forceequation.cpp \
    forcederivative.cpp \
    forcecrossbody.cpp \
    forceactive.cpp \
    force.cpp \
    bodywithsolution.cpp \
    bodywithforcematrix.cpp \
    body.cpp

# Include header files path for libraries
INCLUDEPATH += \
    $$PWD/../../../lib \
    $$PWD/../file_reader \
    $$PWD/../motion_model

# Platform Specific files go in these scope brackets
# ========================================================
win32 {
    # Any files specific to windows go in these brackets.
    LIBS += \
        $$PWD/../../../lib/armadillo.h \
        $$PWD/../../../lib/blas_wind32_MT.lib \
        $$PWD/../../../lib/lapack_win32_MT.lib
}

linux {
    # Any files specific to linux go in these brackets.
    LIBS += -larmadillo -llapack -lblas #Libs for linux filesystem
}
