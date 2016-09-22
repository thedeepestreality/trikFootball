#QMAKE_CXXFLAGS += -std=c++11 -pg -Wno-reorder
#QMAKE_LFLAGS += -pg
#TRIKCONTROL_BINDIR = /opt/trikRuntime/bin/arm-release
#TRIKCONTROL_DIR = /opt/trikRuntime/trikControl

#TRIKCONTROL_BINDIR = /home/captain/trikRuntime-master/bin/arm-release
#TRIKCONTROL_DIR = /home/captain/trikRuntime-master/trikControl

TRIKCONTROL_BINDIR = /home/captain/trikruntime/bin/arm-release
#TRIKKERNEL_DIR = /home/captain/Trik/trikRuntime/trikKernel
TRIKCONTROL_DIR = /home/captain/trikruntime/trikControl
TRIKKERNEL_DIR = /home/captain/trikruntime/trikKernel
TRIK_RUNTIME_DIR = /home/captain/trikruntime

include(/home/captain/trikruntime/trikControl/trikControlExport.pri)

QT       += core
QT       += gui
QT       += network
TARGET = TrikTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH = \
        $$PWD \
        $$TRIKCONTROL_DIR/include \
	$$TRIKKERNEL_DIR/include \

LIBS += -L$$TRIKCONTROL_BINDIR -ltrikControl
LIBS += -L$$TRIKCONTROL_BINDIR -ltrikKernel
LIBS += -L$$TRIKCONTROL_BINDIR -lqslog

!macx {
        QMAKE_LFLAGS += -Wl,-O2,-rpath,.
        QMAKE_CXXFLAGS += -std=c++11
}

HEADERS += \
    test.h

SOURCES += main.cpp \
    test.cpp

