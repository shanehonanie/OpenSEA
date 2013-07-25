TEMPLATE = lib

QT       += core

QT       -= gui

# Define library type
CONFIG += staticlib

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
    body.h \
    activeforcematrix.h

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
    body.cpp \
    activeforcematrix.cpp

# Include header files path for libraries
INCLUDEPATH += \
    $$PWD/../../../lib

# Platform Specific files go in these scope brackets
# ========================================================
win32 {
    # Any files specific to windows go in these brackets.
    LIBS += \
        $$PWD/../../../lib/armadillo.h \
        $$PWD/../../../lib/blas_win32_MT.lib \
        $$PWD/../../../lib/lapack_win32_MT.lib
}

unix {
    # Any files specific to unix go in these brackets.
    LIBS += -larmadillo -llapack -lblas #Libs for unix filesystem
}

# Add dependencies for all previous libs
DEPENDPATH += $${LIBS}



# Add file reader library
unix|win32: LIBS += -L$$OUT_PWD/../file_reader/ -lfile_reader

INCLUDEPATH += $$PWD/../file_reader
DEPENDPATH += $$PWD/../file_reader

win32: PRE_TARGETDEPS += $$OUT_PWD/../file_reader/file_reader.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../file_reader/libfile_reader.a



# Add motion model library
unix|win32: LIBS += -L$$OUT_PWD/../motion_model/ -lmotion_model

INCLUDEPATH += $$PWD/../motion_model
DEPENDPATH += $$PWD/../motion_model

win32: PRE_TARGETDEPS += $$OUT_PWD/../motion_model/motion_model.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../motion_model/libmotion_model.a
