QT       += core gui widgets opengl

TARGET = ORF_2015
TEMPLATE = app

#If Qt 5.3 and 5.4 use this
equals(QT_MINOR_VERSION, 3): QMAKE_CXXFLAGS += -std=c++11
equals(QT_MINOR_VERSION, 4): QMAKE_CXXFLAGS += -std=c++11
#If Qt 5.5 use this:
greaterThan(QT_MINOR_VERSION, 4): CONFIG += c++11


SOURCES += main.cpp \
    camera.cpp \
    cubemaker.cpp \
    statemanager.cpp \
    FileHandler.cpp \
    Vector3.cpp \
    heightmap.cpp \
    GroundHeight.cpp \
    trysil.cpp \
    Triangulate.cpp \
    balls.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h \
    camera.h \
    cubemaker.h \
    statemanager.h \
    transform.h \
    FileHandler.h \
    heightmap.h \
    GroundHeight.h \
    trysil.h \
    Triangulate.h \
    balls.h \
    Vector3.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

DISTFILES += \
    heightmap.bmp
