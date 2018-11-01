#-------------------------------------------------
#
# Project created by QtCreator 2018-10-30T13:39:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZET_PRO
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    subform_one.cpp \
    algorithminstance.cpp \
    rgb2gray.cpp \
    fp_noise.cpp \
    fp_fog.cpp \
    HazeRemover.cpp \
    fp_night.cpp

HEADERS += \
        mainwindow.h \
    subform_one.h \
    algorithminstance.h \
    rgb2gray.h \
    algorithms.h \
    fp_noise.h \
    guidedFilter.hpp \
    fp_fog.h \
    HazeRemover.h \
    fp_night.h

FORMS += \
        mainwindow.ui \
    subform_one.ui


INCLUDEPATH += D:\opencv\opencv-3.2.0\build\include

INCLUDEPATH += D:\opencv\opencv-3.2.0\build\include


CONFIG(debug,debug|release):{
    LIBS += D:\opencv\opencv-3.2.0\build\x64\vc14\lib\opencv_world320d.lib

}else:{
    LIBS += D:\opencv\opencv-3.2.0\build\x64\vc14\lib\opencv_world320.lib
}
