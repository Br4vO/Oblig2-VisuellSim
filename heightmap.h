#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "geometryengine.h"

///Added so I can use Vertex struct. But didnt work
#include "cubemaker.h"
#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

struct VertexDataLOL
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};

class GeometryEngine;

class HeightMap  : protected QOpenGLFunctions
{
public:
    HeightMap();

    void readHeightMap();
    QVector3D normal(QVector3D P1, QVector3D P2, QVector3D P3);
    void drawPlaneGeometry(QOpenGLShaderProgram *program);

    VertexDataLOL mMapData[128*128];

    float getDistfromOrigin() const;
    void setDistfromOrigin(const float a);

private:
    /// Index buffer for indices data for heightmap.
    QOpenGLBuffer indexBuf;
    /// Array buffer for vertex data for heightmap.
    QOpenGLBuffer arrayBuf;
    ///Light position
    GLuint m_lightPosUniform;
    /// Ambient color
    GLuint m_ambientColorUniform;
    /// Diffuse color
    GLuint m_diffuseColorUniform;
    /// Specular color
    GLuint m_specularColorUniform;

    ///Ligth pos and colors:
    QVector3D lightPos = QVector3D(-0.0f, -300.0f, -30.0f);
    //test different ambientColors:
    //QVector3D ambientColor= QVector3D(0.3f, 1.0f, 1.0f);
    //QVector3D ambientColor= QVector3D(0.9f, 0.9f, 1.0f);
    //QVector3D ambientColor= QVector3D(1.0f, 1.0f, 1.0f);
    /// Ambient color
    QVector3D ambientColor = QVector3D(0.0f, 0.0f, 0.0f);
    /// Diffuse color
    QVector3D diffuseColor = QVector3D(0.1f, 0.7f, 0.7f);
    /// Specular color
    QVector3D specularColor = QVector3D(1.0f, 0.0f, 0.0f);

signals:

public slots:
};

#endif // HEIGHTMAP_H
