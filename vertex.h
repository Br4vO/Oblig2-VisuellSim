#ifndef VERTEX_H
#define VERTEX_H

#include <qgl.h>    // definerer GLfloat
#include <iostream>
#include <fstream>

class Vertex
{
    friend std::ostream& operator<< (std::ostream&, const Vertex&);
    friend std::istream& operator>> (std::istream&, Vertex&);
private:
    //GLfloat m_rgba[4];
    GLfloat m_normal[3];
    /// Lager en anonym union siden vi aldri trenger både rgba og normal
    /// Trenger riktignok heller ikke st når vi bruker rgba
    /*union {
        GLfloat m_rgba[4];
        GLfloat m_normal[3];
    };*/
    GLfloat m_st[2];

public:
    Vertex();
    ~Vertex();
    void set_xyz(GLfloat* xyz);
    void set_xyz(GLfloat x, GLfloat y, GLfloat z);
    void set_rgb(GLfloat* rgb);
    void set_rgb(GLfloat r, GLfloat g, GLfloat b);
    void set_normal(GLfloat* normal);
    void set_normal(GLfloat x, GLfloat y, GLfloat z);
    void set_st(GLfloat* st);
    void set_st(GLfloat s, GLfloat t);
    void data(float v[]) const;

        GLfloat m_xyz[3];
};

#endif // VERTEX_H
