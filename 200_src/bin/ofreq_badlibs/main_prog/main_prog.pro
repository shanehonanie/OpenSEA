#-------------------------------------------------
#
# Project created by QtCreator 2013-07-22T19:32:44
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ofreq
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += ofreq.cpp

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

}



#Include Derived Outputs library
unix|win32: LIBS += -L$$OUT_PWD/../derived_outputs/ -lderived_outputs

INCLUDEPATH += $$PWD/../derived_outputs
DEPENDPATH += $$PWD/../derived_outputs

win32: PRE_TARGETDEPS += $$OUT_PWD/../derived_outputs/derived_outputs.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../derived_outputs/libderived_outputs.a



#Include file reader library
unix|win32: LIBS += -L$$OUT_PWD/../file_reader/ -lfile_reader

INCLUDEPATH += $$PWD/../file_reader
DEPENDPATH += $$PWD/../file_reader

win32: PRE_TARGETDEPS += $$OUT_PWD/../file_reader/file_reader.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../file_reader/libfile_reader.a



# Add motion solver library
unix|win32: LIBS += -L$$OUT_PWD/../motion_solver/ -lmotion_solver

INCLUDEPATH += $$PWD/../motion_solver
DEPENDPATH += $$PWD/../motion_solver

win32: PRE_TARGETDEPS += $$OUT_PWD/../motion_solver/motion_solver.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../motion_solver/libmotion_solver.a



# Add file writer library
unix|win32: LIBS += -L$$OUT_PWD/../file_writer/ -lfile_writer

INCLUDEPATH += $$PWD/../file_writer
DEPENDPATH += $$PWD/../file_writer

win32: PRE_TARGETDEPS += $$OUT_PWD/../file_writer/file_writer.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../file_writer/libfile_writer.a
