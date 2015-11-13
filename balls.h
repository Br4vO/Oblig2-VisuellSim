#ifndef BALLS_H
#define BALLS_H

#include <QtGui/QOpenGLShaderProgram>

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

class balls
{
public:
    balls();

    GLfloat m_x;
    GLfloat m_y;
    GLfloat m_z;
    GLfloat m_r;
    GLfloat m_teta;
    GLfloat m_retning;


    Punkt3d v[4];
    Punkt3d ballvertex[8000];
    int antall;

    void lesKoordinater(const char *filnavn);
    void triangle(const Punkt3d &a, const Punkt3d &b, const Punkt3d &c);
    void tetrahedron(int n);
    void normalize (Punkt3d &p);
    void divide_triangle(Punkt3d &a, Punkt3d &b, Punkt3d &c, int n);
    int hentAntall (){return antall;}
};

#endif // BALLS_H
