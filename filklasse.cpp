
#include "filklasse.h"
#include <iostream>
#include <string>

FilKlasse::FilKlasse()
{
    lesSosifil("hoydedata.txt");
}

FilKlasse::~FilKlasse()
{

}

void FilKlasse::skrivfil(std::string filnavn, Vertex vertices[], const int n)
{
    // Opprette (lage) en fil med angitt parameter filnavn
    std::ofstream utfil(filnavn.c_str());

    // Skrive til fil. Skriver først antall linjer og deretter to strenger

    utfil << n << std::endl;
    for (int i=0; i<n; i++)
        utfil << vertices[i] << std::endl;

    // Lukke fil
    utfil.close();
}
/* lesfil() åpner og leser en tekstfil med n Vertex-data
 * n leses inn først og det allokeres minne
*/
void FilKlasse::lesfil(std::string filnavn, Vertex*& vertices, int& n)
{
    // std::cout << "\nFilKlasse::lesfil()" << std::endl;
    // Åpne eksisterende fil
    std::ifstream inn;
    inn.open(filnavn.c_str());
    // Lese punkter - her: linje for linje
    if (inn.is_open())
    {
        inn >> n;
        vertices = new Vertex[n];
        for (int i=0; i<n; i++)
        {
            inn >> vertices[i];
            //std::cout << vertices[i] << std::endl;
            //std::cout << filnavn << std::endl;
        }
    }
    // Lukke fil
    inn.close();
    //std::cout << "Filen er lest." << std::endl;
    //return n;
}

void FilKlasse::lesSosifil(std::string filnavn)
{
    //std::locale();
    std::cout << "\nFilKlasse::lesSosifil()" << std::endl;
    // Åpne eksisterende fil
    std::ifstream inn;
    inn.open(filnavn.c_str());

    int antallPunkter;

    float minX;
    float minY;
    float maxX;
    float maxY;

    //Sjekker om det er lagret en ny høyde før lengde og breddegrader.
    //Laget slik at jeg kan ta inn høyde kurver.
    bool nyHoyde = false;

    // Lese punkter - her: linje for linje
    if (inn.is_open())
    {

        std::string trash;
        std::string test;

        inn >> antallPunkter;
        inn >> maxX;
        inn >> minX;
        inn >> maxY;
        inn >> minY;

        int k = 0;
        float punktNummer;

        while (!inn.eof())
        {

            inn >> trash;
            if (trash == "..HOYDE")
            {
                //std::cout << "fant hoyde!" << std::endl;
                inn >> sosiVertex[k].m_xyz[2];
                //std::cout << "Punkt " << k << " sin z = " << sosiVertex[k].m_xyz[2] << std::endl;
                nyHoyde = true;
            }
            if (trash == "..NO")
            {

                //std::cout << trash << std::endl;
                inn >> trash;
                if (trash != ".KURVE" || trash != ".PUNKT")
                {
                    punktNummer = std::atoi(trash.c_str());
                    sosiVertex[k].m_xyz[0] = punktNummer;
                    inn >> sosiVertex[k].m_xyz[1];
                    sosiVertex[k].m_xyz[0] /= 10000000;
                    sosiVertex[k].m_xyz[1] /= 10000000;
                    // std::cout << trash << std::endl;

                    if (sosiVertex[k].m_xyz[0] <= maxX && sosiVertex[k].m_xyz[0] >= minX && sosiVertex[k].m_xyz[1] <= maxY && sosiVertex[k].m_xyz[1] >= minY)
                    {/*
                        std::cout << "fant lengde bredde!" << std::endl;
                        std::cout << "Punkt " << k << " sin x = " << sosiVertex[k].m_xyz[0] << std::endl;
                        std::cout << "Punkt " << k << " sin y = " << sosiVertex[k].m_xyz[1] << std::endl;*/

                        sosiVertex[k].set_rgb(0,1,0);
                        sosiVertex[k].set_st(0,0);
                        k++;

                        if (nyHoyde == false)
                        {
                            sosiVertex[k].m_xyz[2] = sosiVertex[k-1].m_xyz[2];
                        }

                        nyHoyde = false;
                    }

                }
            }
            if (trash == ".KURVE")
            {
                for (int i = 0; i < 6; i++)
                {
                    inn >> trash;
                }

                //std::cout << "fant hoyde!" << std::endl;
                inn >> sosiVertex[k].m_xyz[2];
                //std::cout << "Punkt " << k << " sin z = " << sosiVertex[k].m_xyz[2] << std::endl;
                //nyHoyde = true;

                for (int i = 0; i < 9; i++)
                {
                    inn >> trash;
                }
                while (trash != ".KURVE")
                {
                    if (k == 20)
                    {
                        break;
                    }
                    //std::cout << trash << std::endl;
                    punktNummer = std::atoi(trash.c_str());
                    sosiVertex[k].m_xyz[0] = punktNummer;
                    inn >> sosiVertex[k].m_xyz[1];
                    sosiVertex[k].m_xyz[0] /= 10000000;
                    sosiVertex[k].m_xyz[1] /= 10000000;
                    // std::cout << trash << std::endl;

                    if (sosiVertex[k].m_xyz[0] <= maxX && sosiVertex[k].m_xyz[0] >= minX && sosiVertex[k].m_xyz[1] <= maxY && sosiVertex[k].m_xyz[1] >= minY)
                    {
                        std::cout << "fant lengde bredde!" << std::endl;
                        std::cout << "Punkt " << k << " sin x = " << sosiVertex[k].m_xyz[0] << std::endl;
                        std::cout << "Punkt " << k << " sin y = " << sosiVertex[k].m_xyz[1] << std::endl;

                        sosiVertex[k].set_rgb(0,1,0);
                        sosiVertex[k].set_st(0,0);
                        k++;

                            sosiVertex[k].m_xyz[2] = sosiVertex[k-1].m_xyz[2];

                        nyHoyde = false;
                    }
                    inn >> trash;
                    //std::cout << trash << std::endl;
                    if (trash == ".SLUTT")
                    {
                        break;
                    }
                }

            }
            std::cout << "k er " << k << ". ";

        }
        std:: cout << "hva er k nå? : " << k <<". ";

        antallPunkterInnenParameter = k;
        std::cout << antallPunkterInnenParameter << std::endl;
    }


    // Lukke fil
    inn.close();
    std::cout << "Filen er lest." << std::endl;
    skrivfil("hoydedata_skrevet_fint.txt", sosiVertex, antallPunkterInnenParameter);

    lesfil("hoydedata_skrevet_fint.txt", sosiVertex, antallPunkterInnenParameter);
    //return n;
    //    int angle;
    //    double determinant;
    //    bool finished = false;

    //    int antallTriangler = 0;
    //    int triangelNummer = 0;

    //    int temp;

    //    int startPunkt = 0;
    //    int venstrePunkt = 1;
    //    int hoyrePunkt = 2;
    //    int testPunkt = 0;

    //    while (finished == false)
    //      {
    //        angle = vinkel(sosiVertex, startPunkt, venstrePunkt, hoyrePunkt);

    //        if (angle <= 0 || angle >= 180)
    //          {
    //            temp = startPunkt;
    //            startPunkt = venstrePunkt;
    //            venstrePunkt = temp;
    //          }
    //        else if (angle >0 && angle < 180)
    //          {
    //            while(testPunkt == startPunkt || testPunkt == venstrePunkt || testPunkt == hoyrePunkt)
    //              {
    //                testPunkt ++;
    //              }

    //            determinant = det(sosiVertex, startPunkt, venstrePunkt, hoyrePunkt, testPunkt);
    //            if (determinant <= 0)
    //              {
    //                triangles[antallTriangler].x =venstrePunkt;
    //                triangles[antallTriangler].y =startPunkt;
    //                triangles[antallTriangler].z = testPunkt;
    //                antallTriangler++;
    //                triangles[antallTriangler].x =testPunkt;
    //                triangles[antallTriangler].y =startPunkt;
    //                triangles[antallTriangler].z = hoyrePunkt;
    //                antallTriangler++;

    //                venstrePunkt = triangles[triangelNummer].x;
    //                startPunkt = triangles[triangelNummer].y;
    //                hoyrePunkt = triangles[triangelNummer].z;
    //                triangelNummer ++;
    //              }
    //          }


    //      }

    ////    angle = vinkel(sosiVertex, k, k+1, k+2);
    ////    determinant = det(sosiVertex, k,k+1,k+2,k+3);

    //    std::cout << "DETERMINANT er " << determinant*1000 << std::endl;


    //    if (angle < 0 || angle > 180)
    //      {
    //        //Ikke Delauney
    //      }
}

float FilKlasse::vinkel(Vertex *vertex, int a, int b, int c)
{
    float u[2];
    float v[2];

    u[0] = (vertex[b].m_xyz[0]-vertex[a].m_xyz[0])*1000;
    u[1] = (vertex[b].m_xyz[1]-vertex[a].m_xyz[1])*1000;

    v[0] = (vertex[c].m_xyz[0]-vertex[a].m_xyz[0])*1000;
    v[1] = (vertex[c].m_xyz[1]-vertex[a].m_xyz[1])*1000;

    float alpha = ((u[0]*v[0])+(u[1]*v[1]))/(qSqrt((u[0]*u[0])+(u[1]*u[1]))*qSqrt((v[0]*v[0])+(v[1]*v[1])));
    //Gjør om fra radianer til grader
    alpha = alpha *(180/3.14);

    std::cout << "u^2 = (" << (u[0]*u[0])+(u[1]*u[1]) << ")" << std::endl;
    std::cout << "v^2 = (" << (v[0]*v[0])+(v[1]*v[1]) << ")" << std::endl;
    std::cout << "u = (" << u[0] << ", " << u[1] << ")" << std::endl;
    std::cout << "v = (" << v[0] << ", " << v[1] << ")" << std::endl;
    std::cout << "alpha er lik " << alpha << std::endl;

    return alpha;

}

double FilKlasse::det(Vertex *vertex, int a, int b, int c, int d)
{
    matrix = QMatrix4x4(vertex[a].m_xyz[0], vertex[a].m_xyz[1], (vertex[a].m_xyz[0]*vertex[a].m_xyz[0])+(vertex[a].m_xyz[1]*vertex[a].m_xyz[1]),1.0f,
            vertex[b].m_xyz[0], vertex[b].m_xyz[1], (vertex[b].m_xyz[0]*vertex[b].m_xyz[0])+(vertex[b].m_xyz[1]*vertex[b].m_xyz[1]),1.0f,
            vertex[c].m_xyz[0], vertex[c].m_xyz[1], (vertex[c].m_xyz[0]*vertex[c].m_xyz[0])+(vertex[c].m_xyz[1]*vertex[c].m_xyz[1]),1.0f,
            vertex[d].m_xyz[0],  vertex[d].m_xyz[1], (vertex[d].m_xyz[0]*vertex[d].m_xyz[0])+(vertex[d].m_xyz[1]*vertex[d].m_xyz[1]),1.0f);
    double determinant;
    determinant = matrix.determinant();
    return determinant;
}



