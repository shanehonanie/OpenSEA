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
    $$PWD/../motion_solver

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
