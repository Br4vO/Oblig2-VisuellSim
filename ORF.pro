QT       += core gui widgets opengl

TARGET = ORF_2015
TEMPLATE = app

#If Qt 5.3 and 5.4 use this
equals(QT_MINOR_VERSION, 3): QMAKE_CXXFLAGS += -std=c++11
equals(QT_MINOR_VERSION, 4): QMAKE_CXXFLAGS += -std=c++11
#If Qt 5.5 use this:
greaterThan(QT_MINOR_VERSION, 4): CONFIG += c++11

win32 {
    INCLUDEPATH += .\\include
    INCLUDEPATH += D:\Spillmotorarkitektur\openal-soft-1.16.0\\include\\AL
    LIBS *= D:\Spillmotorarkitektur\openal-soft-1.16.0\\libs\\libOpenAL32.dll.a
}


SOURCES += main.cpp \
    camera.cpp \
    cubemaker.cpp \
    statemanager.cpp \
    FileHandler.cpp \
    SoundManager.cpp \
    SoundSource.cpp \
    Vector3.cpp \
    heightmap.cpp \
    GroundHeight.cpp \
    trysil.cpp

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
    SoundManager.h \
    SoundSource.h \
    vector3.h \
    heightmap.h \
    GroundHeight.h \
    trysil.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

DISTFILES += \
    heightmap.bmp
