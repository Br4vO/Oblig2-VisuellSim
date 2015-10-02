
#include "filklasse.h"

FilKlasse::FilKlasse()
{

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
    std::cout << "\nFilKlasse::lesfil()" << std::endl;
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
                std::cout << vertices[i] << std::endl;
           }
       }
    // Lukke fil
        inn.close();
        std::cout << "Filen er lest." << std::endl;
    //return n;
}

