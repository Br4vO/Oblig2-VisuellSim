#ifndef VERTEX_H
#define VERTEX_H

#include <qgl.h>

class Vertex
{
private:
    GLfloat m_xyz[3];
    GLfloat m_normal[3]; // Brukes også som rgb
    GLfloat m_st[2];
public:
    Vertex();
    void set_xyz(GLfloat* xyz);
    void set_xyz(GLfloat x, GLfloat y, GLfloat z);
    void set_rgb(GLfloat* rgb);
    void set_rgb(GLfloat r, GLfloat g, GLfloat b);
    void set_normal(GLfloat* normal);
    void set_normal(GLfloat x, GLfloat y, GLfloat z);
    void set_st(GLfloat* st);
    void set_st(GLfloat s, GLfloat t);
    ~Vertex();
};

#endif // VERTEX_H
