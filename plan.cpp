#include <QDebug>
#include <QImage>
#include <cstdio>
//#include <qgl.h>
#include "plan.h"
#include "vertex.h"

Plan::Plan() : DisplayObject()
{
}

Plan::~Plan()
{
    //
}
/// Et bindTexture() kall er gjort
void Plan::setTexture(GLuint texture)
{
    m_tekstur = texture;
    //qDebug() << "Plan::setTexture" << m_tekstur;
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Plan::initVertexBufferObjects()
{
    initializeOpenGLFunctions();

    //qDebug() << "Plan::initVertexBufferObjects - tekstur " << m_tekstur;

    // Lager en array av strukturer med normal, med tekstur koordinater
    Vertex v[6];
    float a=2.0;
    v[0].set_xyz(-a, -a, 0.0);
    v[1].set_xyz( a, -a, 0.0);
    v[2].set_xyz(-a,  a, 0.0);
    v[3].set_xyz(-a,  a, 0.0);
    v[4].set_xyz( a, -a, 0.0);
    v[5].set_xyz( a,  a, 0.0);
    // Tekstur
    v[0].set_st(0.0, 0.0);
    v[1].set_st(1.0, 0.0);
    v[2].set_st(0.0, 1.0);
    v[3].set_st(0.0, 1.0);
    v[4].set_st(1.0, 0.0);
    v[5].set_st(1.0, 1.0);

    for (int i=0; i<6; i++) v[i].set_normal(0.0, 0.0, 1.0);

    // Skal nå sende all vertex og color data til ett buffer
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(Vertex), v, GL_STATIC_DRAW);

    qDebug() << "Plan::initVertexBufferObjects()";
}

void Plan::draw(GLint positionAttribute, GLint normalAttribute, GLint textureAttribute)
{
    static int i;
    // Har en array av strukturer (4 Vertex objekter) som skal splittes på to
    // attributter i vertex shader. stride blir her størrelsen av hver struktur
    // Må bruke offset for start
    initializeOpenGLFunctions();//makeCurrent();
    int offset = 0;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset)); /// stride 3*sizeof(GL_FLOAT) går også bra!?
    offset = 3*sizeof(GLfloat);
    //glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset)); /// stride 3*sizeof(GL_FLOAT) går også bra!?

/// Tekstur
    if (textureAttribute != -1)
    {
        //glUniform1i(colorAttribute, 0);
        offset = 6*sizeof(GLfloat);
        //glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
        glVertexAttribPointer(textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_tekstur);
    }

    //glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    //qDebug() << "Plan::draw() " << ++i;
}
