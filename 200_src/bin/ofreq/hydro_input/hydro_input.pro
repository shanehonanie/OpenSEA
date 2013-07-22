TEMPLATE = lib

QT       += core

QT       -= gui

# Include header files path for libraries
INCLUDEPATH += \
    $$PWD/../../../lib


# Platform Specific files go in these scope brackets
# ========================================================
win32 {
    # Any files specific to windows go in these brackets.

}

linux {
    # Any files specific to linux go in these brackets.
    LIBS += -larmadillo #Libs for linux filesystem
}
