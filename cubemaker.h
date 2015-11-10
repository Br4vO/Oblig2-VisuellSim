#ifndef CUBEMAKER_H
#define CUBEMAKER_H

#include "geometryengine.h"

#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

/// Makes geometryEngine so it can be used in cubemaker.
class GeometryEngine;

class cubemaker  : protected QOpenGLFunctions
{
public:
  /** initializer.
     Does nothing
     */
  cubemaker();
  /** Makes vertexes and indices.
     Fills arrays with vertexes and indices and then puts it in buffer
     @param arrayBuffer - arrayBuffer which gets filled with vertexdata.
     @param indexBuffer - indexBuffer which gets filled with indicesdata.

     */
  void makeCubePls();
  QMatrix4x4 getMatrix();
  void drawCubeGeometry(QOpenGLShaderProgram *program);

private:
  /// Array buffer for vertex data for heightmap.
  QOpenGLBuffer arrayBuf;
  /// Index buffer for indices data for heightmap.
  QOpenGLBuffer indexBuf;
  ///Light position
  GLuint m_lightPosUniform;
  /// Ambient color
  GLuint m_ambientColorUniform;
  /// Diffuse color
  GLuint m_diffuseColorUniform;
  /// Specular color
  GLuint m_specularColorUniform;
  ///Ligth pos and colors:
  QVector3D lightPos = QVector3D(10.0f, 0.0f, 30.0f);
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

#endif // CUBEMAKER_H
