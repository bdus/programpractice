#-------------------------------------------------
#
# Project created by QtCreator 2018-08-08T21:31:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CQLabel
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
    cqlabel.cpp \
    camera.cpp

HEADERS += \
        mainwindow.h \
    cqlabel.h \
    SampleImageCreator.h \
    CameraEventPrinter.h \
    ConfigurationEventPrinter.h \
    ImageEventPrinter.h \
    PixelFormatAndAoiConfiguration.h \
    camera.h

INCLUDEPATH += D:\opencv\cv_contrib340\vscudanopy\install\include \
D:\opencv\cv_contrib340\vscudanopy\install\include\opencv \
D:\opencv\cv_contrib340\vscudanopy\install\include\opencv2 \
    $$quote(D:\Program Files (x86)\led_sdk\Development\include)



LIBS += D:\opencv\cv_contrib340\vscudanopy\install\x64\vc14\lib\opencv_world340d.lib \
   $$quote(D:\Program Files (x86)\led_sdk\Development\lib\x64\*.lib)



FORMS += \
        mainwindow.ui
