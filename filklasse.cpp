
#include "filklasse.h"

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
        inn >> antallPunkter;
        inn >> maxX;
        inn >> minX;
        inn >> maxY;
        inn >> minY;

        int k = 0;
        while (!inn.eof())
        {
            inn >> trash;
            if (trash == "..HOYDE")
            {
                std::cout << "fant hoyde!" << std::endl;
                inn >> sosiVertex[k].m_xyz[2];
                sosiVertex[k].m_xyz[2] /= 100;
                std::cout << "Punkt " << k << " sin z = " << sosiVertex[k].m_xyz[2] << std::endl;
                nyHoyde = true;
            }
            if (trash == "..NO")
            {
                inn >> sosiVertex[k].m_xyz[0];
                inn >> sosiVertex[k].m_xyz[1];
                sosiVertex[k].m_xyz[0] /= 10000000;
                sosiVertex[k].m_xyz[1] /= 10000000;

                if (sosiVertex[k].m_xyz[0] <= maxX && sosiVertex[k].m_xyz[0] >= minX && sosiVertex[k].m_xyz[1] <= maxY && sosiVertex[k].m_xyz[1] >= minY)
                  {
                  std::cout << "fant lengde bredde!" << std::endl;
                  std::cout << "Punkt " << k << " sin x = " << sosiVertex[k].m_xyz[0] << std::endl;
                  std::cout << "Punkt " << k << " sin y = " << sosiVertex[k].m_xyz[1] << std::endl;

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
        antallPunkterInnenParameter = k;
    }



    // Lukke fil
    inn.close();
    std::cout << "Filen er lest." << std::endl;
    skrivfil("hoydedata_skrevet_fint.txt", sosiVertex, antallPunkterInnenParameter);

    lesfil("hoydedata_skrevet_fint.txt", sosiVertex, antallPunkterInnenParameter);
    //return n;
}



