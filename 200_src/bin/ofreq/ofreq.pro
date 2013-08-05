#-------------------------------------------------
#
# Project created by QtCreator 2013-07-22T19:56:40
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ofreq
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += ofreq.cpp \
    derived_outputs/outputslist.cpp \
    derived_outputs/outputsbody.cpp \
    derived_outputs/outputderived.cpp \
    derived_outputs/globalvelocity.cpp \
    derived_outputs/globalsolution.cpp \
    derived_outputs/globalmotion.cpp \
    derived_outputs/globalacceleration.cpp \
    file_reader/seaenvinput.cpp \
    file_reader/readinputfile.cpp \
    file_reader/hydrodynamicinput.cpp \
    file_reader/forcesinput.cpp \
    file_reader/datainput.cpp \
    file_reader/controlinput.cpp \
    file_reader/bodiesinput.cpp \
    file_writer/filewriter.cpp \
    file_writer/filewavefrequencies.cpp \
    file_writer/filewavedirections.cpp \
    file_writer/filelist.cpp \
    global_objects/wavefrequencies.cpp \
    global_objects/wavedirections.cpp \
    global_objects/system.cpp \
    motion_solver/userforces.cpp \
    motion_solver/motionsolver.cpp \
    motion_solver/forceactive.cpp \
    motion_solver/force.cpp \
    motion_solver/body.cpp \
    wave_calcs/wavespreadmodel.cpp \
    wave_calcs/wavespectrummodel.cpp \
    wave_calcs/seaenviroment.cpp \
    motion_solver/matreactforce.cpp \
    motion_solver/matbody.cpp \
    motion_solver/matcrossforce.cpp \
    motion_model/equationofmotion.cpp \
    motion_model/motionmodel.cpp \
    motion_solver/forcecross.cpp \
    motion_solver/forcereact.cpp \
    motion_solver/derivative.cpp \
    motion_solver/equation.cpp \
    motion_solver/matactiveforce.cpp

HEADERS += \
    derived_outputs/outputslist.h \
    derived_outputs/outputsbody.h \
    derived_outputs/outputderived.h \
    derived_outputs/globalvelocity.h \
    derived_outputs/globalsolution.h \
    derived_outputs/globalmotion.h \
    derived_outputs/globalacceleration.h \
    file_reader/seaenvinput.h \
    file_reader/readinputfile.h \
    file_reader/hydrodynamicinput.h \
    file_reader/forcesinput.h \
    file_reader/datainput.h \
    file_reader/controlinput.h \
    file_reader/bodiesinput.h \
    file_writer/filewriter.h \
    file_writer/filewavefrequencies.h \
    file_writer/filewavedirections.h \
    file_writer/filelist.h \
    global_objects/wavefrequencies.h \
    global_objects/wavedirections.h \
    global_objects/system.h \
    motion_solver/userforces.h \
    motion_solver/motionsolver.h \
    motion_solver/forceactive.h \
    motion_solver/force.h \
    motion_solver/body.h \
    wave_calcs/wavespreadmodel.h \
    wave_calcs/wavespectrummodel.h \
    wave_calcs/seaenviroment.h \
    motion_solver/matbody.h \
    motion_solver/matcrossforce.h \
    motion_solver/matreactforce.h \
    motion_model/equationofmotion.h \
    motion_model/motionmodel.h \
    motion_solver/forcecross.h \
    motion_solver/forcereact.h \
    motion_solver/derivative.h \
    motion_solver/equation.h \
    motion_solver/matactiveforce.h

# Include header files path for libraries
INCLUDEPATH += \
    $$PWD/../../../lib \
    $$PWD/../../../var

# force rebuild if the headers change
DEPENDPATH += $${INCLUDEPATH}

OTHER_FILES += \
    ../../var/openseaheader.txt

# Platform Specific files go in these scope brackets
# ========================================================
win32 {
    # Any files specific to windows go in these brackets.
    LIBS += \
        $$PWD/../../../lib/armadillo.h \        #Add armadillo and associated support
        $$PWD/../../../lib/blas_win32_MT.lib \
        $$PWD/../../../lib/lapack_win32_MT.lib
    LIBS += boost_system boost_filesystem   # Add boost and boost filesystem
}

unix {
    # Any files specific to linux go in these brackets.
    LIBS += -larmadillo -llapack -lblas #Add armadillo and associated support
    LIBS += -lboost_system -lboost_filesystem   # Add boost and boost filesystem
}
