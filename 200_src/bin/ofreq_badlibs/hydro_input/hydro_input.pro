TEMPLATE = lib

QT       += core

QT       -= gui

# Define library type
CONFIG += staticlib

# Include header files path for libraries
INCLUDEPATH += \
    $$PWD/../../../lib


# Platform Specific files go in these scope brackets
# ========================================================
win32 {
    # Any files specific to windows go in these brackets.

}

unix {
    # Any files specific to unix go in these brackets.
    LIBS += -larmadillo #Libs for unix filesystem
}
