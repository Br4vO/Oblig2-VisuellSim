QT       += core gui widgets opengl

TARGET = ORF_2015
TEMPLATE = app

#If Qt 5.3 and 5.4 use this
equals(QT_MINOR_VERSION, 3): QMAKE_CXXFLAGS += -std=c++11
equals(QT_MINOR_VERSION, 4): QMAKE_CXXFLAGS += -std=c++11
#If Qt 5.5 use this:
greaterThan(QT_MINOR_VERSION, 4): CONFIG += c++11


SOURCES += main.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h

RESOURCES += \
    shaders.qrc \
    textures.qrc
