#-------------------------------------------------
#
# Project created by QtCreator 2013-05-25T11:11:50
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = oFreq_Linux
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    wavespreadmodel.cpp \
    wavespectrummodel.cpp \
    wavefrequencies.cpp \
    wavedirections.cpp \
    userforces.cpp \
    system.cpp \
    seaenviroment.cpp \
    seaenvinput.cpp \
    readinputfile.cpp \
    reactiveforcematrix.cpp \
    motionsolver.cpp \
    motionmodel.cpp \
    hydrodynamicinput.cpp \
    forcesinput.cpp \
    forcereactive.cpp \
    forceequation.cpp \
    forcederivative.cpp \
    forcecrossbody.cpp \
    forceactive.cpp \
    force.cpp \
    equationofmotion_01.cpp \
    equationofmotion.cpp \
    datainput.cpp \
    controlinput.cpp \
    bodywithforcematrix.cpp \
    body.cpp \
    bodiesinput.cpp \
    activeforcematrix.cpp \
    filewavefrequencies.cpp \
    filewavedirections.cpp \
    outputslist.cpp \
    outputsbody.cpp \
    outputderived.cpp \
    globalvelocity.cpp \
    globalsolution.cpp \
    globalmotion.cpp \
    globalacceleration.cpp \
    ofreq.cpp \
    filewriter.cpp \
    bodywithsolution.cpp \
    filelist.cpp

OTHER_FILES += \
    seaenv.in \
    forces.in \
    data.in \
    control.in \
    bodies.in \
    OpenSeaHeader.txt \
    frequencies.out \
    directions.out \
    d0velglobal.out \
    d0motglobal.out \
    d0accglobal.out

HEADERS += \
    wavespreadmodel.h \
    wavespectrummodel.h \
    wavefrequencies.h \
    wavedirections.h \
    userforces.h \
    system.h \
    seaenviroment.h \
    seaenvinput.h \
    readinputfile.h \
    reactiveforcematrix.h \
    motionsolver.h \
    motionmodel.h \
    hydrodynamicinput.h \
    forcesinput.h \
    forcereactive.h \
    forceequation.h \
    forcederivative.h \
    forcecrossbody.h \
    forceactive.h \
    force.h \
    equationofmotion_01.h \
    equationofmotion.h \
    datainput.h \
    controlinput.h \
    bodywithforcematrix.h \
    body.h \
    bodiesinput.h \
    activeforcematrix.h \
    filewavefrequencies.h \
    filewavedirections.h \
    filelist.h \
    outputsbody.h \
    outputderived.h \
    globalvelocity.h \
    globalsolution.h \
    globalmotion.h \
    globalacceleration.h \
    filewriter.h \
    bodywithsolution.h

LIBS += -larmadillo -llapack -lblas -lboost_system -lboost_filesystem
