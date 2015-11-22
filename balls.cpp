#include "balls.h"
#include <cmath>
#include <QDebug>
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;

Balls::Balls(float x, float y, float z) : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_r(0.5f), m_teta(0.0f), m_retning(-1.0f)
{
    antall = 0;
    mGround = new GroundHeight;
    mHeight = new HeightMap;
    mCamera = new Camera;

    ballTransform.mPosition = QVector3D(x, y, z);
}

void Balls::createBall()
{
    initializeOpenGLFunctions();

    lesKoordinater("ball.txt");
    tetrahedron(3);
    arrayBuf.create();
    arrayBuf.bind();
    arrayBuf.allocate(ballvertex, 8000 * sizeof(GLfloat));
}

void Balls::lesKoordinater(const char *filnavn)
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
    }
}

void Balls::triangle(const Punkt3d &a, const Punkt3d &b, const Punkt3d &c)
{
    ballvertex[antall] = a;
    antall++;
    ballvertex[antall] = b;
    antall++;
    ballvertex[antall] = c;
    antall++;
}

void Balls::tetrahedron(int n)
{
    divide_triangle(v[0], v[1], v[2], n);
    divide_triangle(v[3], v[2], v[1], n);
    divide_triangle(v[0], v[3], v[1], n);
    divide_triangle(v[0], v[2], v[3], n);
}

void Balls::normalize(Punkt3d &p)
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

void Balls::divide_triangle(Punkt3d &a, Punkt3d &b, Punkt3d &c, int n)
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

QVector3D Balls::updateBall()
{
    QVector3D temp;
    int i;
    temp = ballTransform.mPosition;
    i = mGround->findVertex(temp);
    temp = mGround->findGround(temp);
    akselerasjon = (mHeight->mMapData[i].normal + QVector3D(0.0f, gravity, 0.0f)) * gravity * mHeight->mMapData[i].normal.y();

    //Ballen er på plane. Se hva som skjer!
    if(ballTransform.mPosition.y() <= temp.y())
    {
        //qDebug() << "i er " << i;
        temp +=  QVector3D(mHeight->mMapData[i].normal.x(), 0, mHeight->mMapData[i].normal.z())*akselerasjon;
        //qDebug() << "Normalen er " << mHeight->mMapData[i].normal;
        akselerasjon *= 0.99;

        // Stop rotation when speed goes below threshold
        if (akselerasjon.x()+akselerasjon.y()+akselerasjon.z() < 0.01)
        {
            akselerasjon = QVector3D(0.0,0.0,0.0);
        }
    }

    //Dette skjer dersom ballen ikke er nedi planet enda
    else{
        temp.setY(temp.y() - gravity);
    }
//    qDebug() << "Planet er " << temp;
//    qDebug() << "Player er " <<  ballTransform.mPosition;
//    qDebug() << "mMapData[i]"  << mHeight->mMapData[i].position;
    //mCamera->mViewMatrix.translate

    QVector3D moveCamera = QVector3D(-(temp.x()-ballTransform.mPosition.x()), -(temp.y()-ballTransform.mPosition.y()), -(temp.z()-ballTransform.mPosition.z()));
    ballTransform.mPosition = temp;
    return moveCamera;
}

void Balls::drawBall(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, 8*sizeof(GLfloat));
    // Offset for texture coordinate
    offset += 3 * sizeof(GLfloat);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, 8*sizeof(GLfloat));

    // Offset for normals coordinate
    offset += 2 * sizeof(GLfloat);

    int normalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, 8* sizeof(GLfloat));
     //qDebug() << vertexLocation << " " << texcoordLocation << " " << normalLocation;
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
    glDrawArrays(GL_TRIANGLES, 0, 8000);
}

