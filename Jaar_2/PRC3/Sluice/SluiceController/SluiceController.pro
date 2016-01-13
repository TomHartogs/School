QT       += core websockets gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = echoclient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    client.cpp \
    sluicedoor.cpp \
    sluice.cpp \
    sluicevalve.cpp \
    onesecondvalve.cpp \
    sluicecontroller.cpp \
    mainwindow.cpp

HEADERS += \
    client.h \
    sluicedoor.h \
    state_enum.h \
    sluice.h \
    sluicevalve.h \
    onesecondvalve.h \
    sluicecontroller.h \
    mainwindow.h

DISTFILES +=

FORMS += \
    mainwindow.ui
