#include "balls.h"
#include <cmath>
#include <QDebug>
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;

/// Struct which holds position, texturcoordinates and normals for each vertex.
struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};

balls::balls() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_r(0.5f), m_teta(0.0f), m_retning(-1.0f)
{
    antall = 0;
}

void balls::lesKoordinater(const char *filnavn)
{
  ifstream innfil(filnavn);
  for (int i =0; i <= 3; i ++)
    {
      innfil >> v[i].m_x;
      innfil >> v[i].m_y;
      innfil >> v[i].m_z;
      innfil >> v[i].m_R;
      innfil >> v[i].m_G;
      innfil >> v[i].m_B;
      innfil >> v[i].m_S;
      innfil >> v[i].m_T;
      qDebug() << "v[" << i << "].m_x = " << v[i].m_x;
      qDebug() << "v[" << i << "].m_y = " << v[i].m_y;
      qDebug() << "v[" << i << "].m_z = " << v[i].m_z;
    }
}

void balls::triangle(const Punkt3d &a, const Punkt3d &b, const Punkt3d &c)
  {
    ballvertex[antall] = a;
    antall++;
    ballvertex[antall] = b;
    antall++;
    ballvertex[antall] = c;
    antall++;
  }

void balls::tetrahedron(int n)
{
    divide_triangle(v[0], v[1], v[2], n);
    divide_triangle(v[3], v[2], v[1], n);
    divide_triangle(v[0], v[3], v[1], n);
    divide_triangle(v[0], v[2], v[3], n);
}

void balls::normalize(Punkt3d &p)
{
    float d=0.0;

    d+=p.m_x * p.m_x;
    d+=p.m_y * p.m_y;
    d+=p.m_z * p.m_z;

    d=sqrt(d);
    if(d > 0.0)
    {
       p.m_x = p.m_x/d;
       p.m_y = p.m_y/d;
       p.m_z = p.m_z/d;
    }
}

void balls::divide_triangle(Punkt3d &a, Punkt3d &b, Punkt3d &c, int n)
{
  Punkt3d v1, v2, v3;

  if(n > 0)
  {
      v1.m_x=a.m_x+b.m_x;
      v1.m_y=a.m_y+b.m_y;
      v1.m_z=a.m_z+b.m_z;
      normalize(v1);

      v2.m_x=a.m_x + c.m_x;
      v2.m_y=a.m_y + c.m_y;
      v2.m_z=a.m_z + c.m_z;
      normalize(v2);

      v3.m_x=c.m_x + b.m_x;
      v3.m_y=c.m_y + b.m_y;
      v3.m_z=c.m_z + b.m_z;
      normalize(v3);

      divide_triangle(a, v2, v1, n-1);
      divide_triangle(c, v3, v2, n-1);
      divide_triangle(b, v1, v3, n-1);
      divide_triangle(v1, v2, v3, n-1);
  }
  else triangle(a, b, c);
}

void balls::drawBall(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use

    indexBuf.bind();
    arrayBuf.bind();
    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Offset for normals coordinate
    offset += sizeof(QVector2D);

    int normalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

     // qDebug() << vertexLocation << " " << texcoordLocation << " " << normalLocation;
    //Enables the light:
    //These first lines should be in an init-function
    m_lightPosUniform = program->uniformLocation("lightPosition");
    m_ambientColorUniform = program->uniformLocation("ambientColor");
    m_diffuseColorUniform = program->uniformLocation("diffuseColor");
    m_specularColorUniform = program->uniformLocation("specularColor");

    program->enableAttributeArray(m_lightPosUniform);
    program->enableAttributeArray(m_ambientColorUniform);
    program->enableAttributeArray(m_diffuseColorUniform);
    program->enableAttributeArray(m_specularColorUniform);

    program->setUniformValue(m_lightPosUniform, lightPos);
    //m_program->setUniformValue(m_ambientColorUniform, tempAmbient);
    program->setUniformValue(m_ambientColorUniform, ambientColor);
    program->setUniformValue(m_diffuseColorUniform, diffuseColor);
    program->setUniformValue(m_specularColorUniform, specularColor);


    // Draw cube geometry using indices from VBO 1
    glDrawArrays(GL_TRIANGLES, 0, antall);
}
