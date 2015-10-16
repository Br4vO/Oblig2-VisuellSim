#-------------------------------------------------
#
# Project created by QtCreator 2015-01-13T12:03:14
#
#-------------------------------------------------

QT       += core gui
QT += opengl
QT += gui
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 130523GLWidget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    displayobject.cpp \
    plan.cpp \
    shaderprogram.cpp \
    vertex.cpp \
    glwidget.cpp \
    texture.cpp \
    filklasse.cpp

HEADERS  += mainwindow.h \
    displayobject.h \
    glwidget.h \
    plan.h \
    shaderprogram.h \
    vertex.h \
    texture.h \
    filklasse.h \
    vec3.h
