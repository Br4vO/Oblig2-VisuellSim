
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
         std::string hoydeLetters = "..HØYDE";
         std::string logbLetters = "..NØ";
         bool hoyde = false;
         bool logb = false;
         inn >> antallLinjer;
         inn >> antallPunkter;
         sosiVertex = new Vertex[antallPunkter];
         int k = 0;
         for (int i=0; i<antallLinjer; i++)
         {
             if (hoyde == true)
               {
                 inn >> sosiVertex[k].m_xyz[2];
                 hoyde = false;
                 std::cout << inn << std::endl;
               }
             if (logb == true)
               {
                 inn >> sosiVertex[k].m_xyz[0];
                 inn >> sosiVertex[k].m_xyz[1];
                 logb = false;
                 std::cout << inn << std::endl;
                 k++;
               }
              inn >> trash;
             if (trash == "..HØYDE")
               {
                hoyde = true;
               std::cout << "fant hoyde!" << std::endl;
               }
             if (trash == "..NØ")
               {
                 logb = true;
                 std::cout << "fant lengde bredde!" << std::endl;
               }
           std::cout << trash << std::endl;
           std::cout << hoydeLetters << std::endl;
           std::cout << logbLetters << std::endl;
         }
//         for (int i=0; i<antallPunkter; i++)
//           {
//             for (int k=0; k < 3; k++)
//               {
//               std::cout << sosiVertex[i].m_xyz[k] << std::endl;
//               std::cout << "HI" << std::endl;
//               }
//           }
     }
  // Lukke fil
      inn.close();
      std::cout << "Filen er lest." << std::endl;
      //return n;
}



