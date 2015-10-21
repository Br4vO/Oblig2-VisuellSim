#ifndef FILKLASSE_H
#define FILKLASSE_H

#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <QtCore/qmath.h>
#include "vertex.h"
#include "vec3.h"
#include <QMatrix4x4>

class FilKlasse
{
public:
    int antall;
    int antallPunkterInnenParameter;
    std::string ordliste[10];

    Vertex* sosiVertex = new Vertex[50];
    Vec3 triangles;
    QMatrix4x4 matrix;

    FilKlasse();
    ~FilKlasse();
    void skrivfil(std::string filnavn, Vertex vertices[], const int n);
    void lesfil(std::string filnavn, Vertex *&vertices, int& n);
    void lesSosifil (std::string filnavn);
private:
    float vinkel(Vertex* vertex, int a, int b, int c);
    double det(Vertex* vertex, int a, int b, int c, int d);
};

#endif // FILKLASSE_H
