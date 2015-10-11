#-------------------------------------------------
#
# Project created by QtCreator 2015-10-08T15:04:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceDetec
TEMPLATE = app



INCLUDEPATH+=D:\OpenCV\include\opencv\
             D:\OpenCV\include\opencv2\
             D:\OpenCV\include


LIBS+=D:\OpenCV\lib\libopencv_calib3d2410.dll.a\
        D:\OpenCV\lib\libopencv_contrib2410.dll.a\
        D:\OpenCV\lib\libopencv_core2410.dll.a\
        D:\OpenCV\lib\libopencv_features2d2410.dll.a\
        D:\OpenCV\lib\libopencv_flann2410.dll.a\
        D:\OpenCV\lib\libopencv_gpu2410.dll.a\
        D:\OpenCV\lib\libopencv_highgui2410.dll.a\
        D:\OpenCV\lib\libopencv_imgproc2410.dll.a\
        D:\OpenCV\lib\libopencv_legacy2410.dll.a\
        D:\OpenCV\lib\libopencv_ml2410.dll.a\
        D:\OpenCV\lib\libopencv_objdetect2410.dll.a\
        D:\OpenCV\lib\libopencv_video2410.dll.a

SOURCES += main.cpp\
        mainwindow.cpp \
    facedetect.cpp \
    facerecognize.cpp

HEADERS  += mainwindow.h \
    facedetect.h \
    facerecognize.h

FORMS    += mainwindow.ui
