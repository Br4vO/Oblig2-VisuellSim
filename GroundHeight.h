#ifndef GROUNDHEIGHT_H
#define GROUNDHEIGHT_H

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QKeyEvent>
#include "qdebug.h"

#include "HeightMap.h"
#include "geometryengine.h"

class HeightMap;
class GeometryEngine;

class GroundHeight
{
public:
    GroundHeight();
    QVector3D findGround(QVector3D &playerPos);

private:
    HeightMap *mMap;
    GeometryEngine *geometries;
};

#endif // GROUNDHEIGHT_H
