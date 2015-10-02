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

    FilKlasse();
    ~FilKlasse();
    void skrivfil(std::string filnavn, Vertex vertices[], const int n);
    void lesfil(std::string filnavn, Vertex *&vertices, int& n);
};

#endif // FILKLASSE_H
