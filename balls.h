#ifndef BALLS_H
#define BALLS_H

#include <QtGui/QOpenGLShaderProgram>
#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include "transform.h"
#include "GroundHeight.h"
#include "heightmap.h"
#include "camera.h"

struct Punkt3d
{
    float m_x;
    float m_y;
    float m_z;
    float m_R;
    float m_G;
    float m_B;
    float m_S;
    float m_T;
};

class GroundHeight;
class HeightMap;
class Camera;

class Balls  : protected QOpenGLFunctions
{
public:
    Balls(float x, float y, float z);

    GLfloat m_x;
    GLfloat m_y;
    GLfloat m_z;
    GLfloat m_r;
    GLfloat m_teta;
    GLfloat m_retning;

    Transform ballTransform;
    Punkt3d v[4];
    Punkt3d ballvertex[8000];
    int antall;

    void createBall();
    void lesKoordinater(const char *filnavn);
    void triangle(const Punkt3d &a, const Punkt3d &b, const Punkt3d &c);
    void tetrahedron(int n);
    void normalize (Punkt3d &p);
    void divide_triangle(Punkt3d &a, Punkt3d &b, Punkt3d &c, int n);
    int hentAntall (){return antall;}
    QVector3D updateBall();

    void drawBall(QOpenGLShaderProgram *program);

private:
    GroundHeight *mGround;
    HeightMap *mHeight;
    Camera *mCamera;

    float gravity = 0.098f;
    QVector3D akselerasjon;

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

#endif // BALLS_H
