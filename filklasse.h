#ifndef FILKLASSE_H
#define FILKLASSE_H

#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include "vertex.h"

class FilKlasse
{
public:
    int antall;
    std::string ordliste[10];

    Vertex* sosiVertex;

    FilKlasse();
    ~FilKlasse();
    void skrivfil(std::string filnavn, Vertex vertices[], const int n);
    void lesfil(std::string filnavn, Vertex *&vertices, int& n);
    void lesSosifil (std::string filnavn);
};

#endif // FILKLASSE_H
