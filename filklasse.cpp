
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
  // Lese punkter - her: linje for linje
     if (inn.is_open())
     {
         int antallLinjer;
         int antallPunkter;
         std::string trash;
         inn >> antallLinjer;
         inn >> antallPunkter;
         sosiVertex = new Vertex[antallPunkter];
         int k = 0;
         while (!inn.eof())
         {
              inn >> trash;
             if (trash == "..HOYDE")
               {
                //hoyde = true;
               std::cout << "fant hoyde!" << std::endl;
               inn >> sosiVertex[k].m_xyz[2];
               sosiVertex[k].m_xyz[2] /= 100;
               std::cout << "Punkt " << k << " sin z = " << sosiVertex[k].m_xyz[2] << std::endl;
               }
             if (trash == "..NO")
               {
                 inn >> sosiVertex[k].m_xyz[0];
                 inn >> sosiVertex[k].m_xyz[1];
                 sosiVertex[k].m_xyz[0] /= 10000;
                 sosiVertex[k].m_xyz[1] /= 10000;
                 std::cout << "fant lengde bredde!" << std::endl;
                 std::cout << "Punkt " << k << " sin x = " << sosiVertex[k].m_xyz[0] << std::endl;
                 std::cout << "Punkt " << k << " sin y = " << sosiVertex[k].m_xyz[1] << std::endl;
                 k++;
               }
         }
     }
  // Lukke fil
      inn.close();
      std::cout << "Filen er lest." << std::endl;
      skrivfil("hoydedata_skrevet_fint", sosiVertex, 150);
      //return n;
}



