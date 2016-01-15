QT       += core websockets gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SluiceController
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    client.cpp \
    sluicedoor.cpp \
    sluice.cpp \
    sluicecontroller.cpp \
    valve.cpp \
    normalvalve.cpp \
    normalsluicedoor.cpp \
    onesecondsluicedoor.cpp \
    water.cpp

HEADERS += \
    client.h \
    sluicedoor.h \
    sluice.h \
    sluicecontroller.h \
    valve.h \
    normalvalve.h \
    normalsluicedoor.h \
    enum.h \
    onesecondsluicedoor.h \
    water.h

DISTFILES +=

FORMS += \
    mainwindow.ui
