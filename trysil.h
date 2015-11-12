#ifndef TRYSIL_H
#define TRYSIL_H

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include "Triangulate.h"

struct VertexDataTrysil
{
    GLfloat m_xyz[3];
    QVector2D texCoord;
    QVector3D normal;
};

class Triangulate;

class trysil : protected QOpenGLFunctions
{
public:
  trysil();
  void lesSosifil(std::string filnavn);
  void drawTrysilGeometry(QOpenGLShaderProgram *program);

private:
  Triangulate* tri;

  VertexDataTrysil* sosiVertex = new VertexDataTrysil[100000];
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
};

#endif // TRYSIL_H
