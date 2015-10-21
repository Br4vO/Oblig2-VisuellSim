#include <QDebug>
#include <QImage>
#include <cstdio>
#include <iostream>
//#include <qgl.h>
#include "plan.h"
#include "vertex.h"
#include "filklasse.h"

Plan::Plan() : DisplayObject()
{
    //m_vertices = new Vertex[10];
    lesfil("hoydedata.txt");
   //for (int i=0; i<10; i++)
   //    m_vertices[i] = new Vertex();
}

Plan::~Plan()
{
    //
    qDebug() << "Plan::~Plan()";
    delete [] m_vertices;
}

void Plan::lesfil(std::string filnavn)
{
    std::cout << "Plan::lesfil()";
    fk.lesfil(filnavn, m_vertices, m_antallVertices);
    std::cout << "antall " << m_antallVertices << std::endl;
    //for (int i=0; i<m_antallVertices; i++)
        //std::cout << m_vertices[i] << " fra Plan::lesfil()" << std::endl;
}
void Plan::data(float v[48]) const
{
    //int k=0;
    for (int i=0; i<m_antallVertices; i++)
    {
        float vdata[8];
        m_vertices[i].data(vdata);
//        for (int j=0; j<8; j++)
//            v[k++] = vdata[j];
    }
}
void Plan::initVertexBufferObjects()
{
    initializeOpenGLFunctions();

    // Unødvendig å gjøre dette, siden m_vertices kan sendes inn uten cast med glBufferData
    float* bufferData = new float[48];
    data(bufferData);

    // Skal nå sende all vertex og color data til ett buffer
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, fk.antallPunkterInnenParameter*sizeof(Vertex), fk.sosiVertex, GL_STATIC_DRAW);

    //glGenBuffers(1, &m_colorBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    //glBufferData(GL_ARRAY_BUFFER, 16*sizeof(GLfloat), colors, GL_STATIC_DRAW);

    //glGenBuffers(1, &m_indexBuffer);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12*sizeof(GLubyte), indices, GL_STATIC_DRAW);
    qDebug() << "Plan::initVertexBufferObjects()";
}

void Plan::draw(GLint positionAttribute, GLint normalAttribute, GLint textureAttribute)
{
    // Har en array av strukturer (4 Vertex objekter) som skal splittes på to
    // attributter i vertex shader. stride blir her størrelsen av hver struktur
    // Må bruke offset for start
    initializeOpenGLFunctions();//makeCurrent();
    int offset = 0;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset)); /// stride 3*sizeof(GL_FLOAT) går også bra!?
    offset = 3*sizeof(GLfloat);
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset)); /// stride 3*sizeof(GL_FLOAT) går også bra!?
    //qDebug() << "Plan draw" << positionAttribute << normalAttribute << textureAttribute;
    //qDebug() << sizeof(Vertex);
    // Tekstur
//    if (textureAttribute != -1)
//    {
//        //glUniform1i(colorAttribute, 0);
//        offset = 6*sizeof(GLfloat);
//        //glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
//        glVertexAttribPointer(textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset));
//        //glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, m_texture);
//    }

    //glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glDrawArrays(GL_TRIANGLES, 0, fk.antallPunkterInnenParameter);
    //qDebug() << "Plan::draw() " << ++i;
}
