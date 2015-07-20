#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T16:13:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CPSC453A3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    intersection.cpp \
    sphere.cpp \
    plane.cpp \
    triangle.cpp \
    material.cpp \
    light.cpp

HEADERS  += mainwindow.h \
    shape.h \
    intersection.h \
    sphere.h \
    plane.h \
    triangle.h \
    material.h \
    light.h

FORMS    += mainwindow.ui
