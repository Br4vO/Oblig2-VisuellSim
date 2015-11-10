#include "trysil.h"
#include <iostream>
#include <string>

trysil::trysil() : indexBuf(QOpenGLBuffer::IndexBuffer)
{
  initializeOpenGLFunctions();
  lesSosifil("hoydedata.txt");
}

void trysil::lesSosifil(std::string filnavn)
{
    std::cout << "\nFilKlasse::lesSosifil()" << std::endl;
    // Åpne eksisterende fil
    std::ifstream inn;
    inn.open(filnavn.c_str());

    int antallPunkter;

    float minX;
    float minY;
    float maxX;
    float maxY;
    int antallPunkterInnenParameter;

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
        float punktNummer;

        while (!inn.eof())
        {

            inn >> trash;
            if (trash == "..HOYDE")
            {
                std::cout << "fant hoyde!" << std::endl;
                inn >> sosiVertex[k].m_xyz[1];
                std::cout << "Punkt " << k << " sin z = " << sosiVertex[k].m_xyz[2] << std::endl;
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
                    inn >> sosiVertex[k].m_xyz[2];
                    sosiVertex[k].m_xyz[0] /= 10000000;
                    sosiVertex[k].m_xyz[2] /= 10000000;
                    // std::cout << trash << std::endl;

                    if (sosiVertex[k].m_xyz[0] <= maxX && sosiVertex[k].m_xyz[0] >= minX && sosiVertex[k].m_xyz[2] <= maxY && sosiVertex[k].m_xyz[2] >= minY)
                    {
                        std::cout << "fant lengde bredde!" << std::endl;
                        std::cout << "Punkt " << k << " sin x = " << sosiVertex[k].m_xyz[0] << std::endl;
                        std::cout << "Punkt " << k << " sin y = " << sosiVertex[k].m_xyz[1] << std::endl;

                        sosiVertex[k].normal = QVector3D(0.0f,1.0f,0.0f);
                        sosiVertex[k].texCoord= QVector2D(0.0f,0.0f);
                        k++;

                        if (nyHoyde == false)
                        {
                            sosiVertex[k].m_xyz[1] = sosiVertex[k-1].m_xyz[1];
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

                std::cout << "fant hoyde!" << std::endl;
                inn >> sosiVertex[k].m_xyz[1];
                sosiVertex[k].m_xyz[1];
                std::cout << "Punkt " << k << " sin z = " << sosiVertex[k].m_xyz[2] << std::endl;
                //nyHoyde = true;

                for (int i = 0; i < 9; i++)
                {
                    inn >> trash;
                }
                while (trash != ".KURVE")
                {
//                    if (k == 20)
//                    {
//                        break;
//                    }
                    //std::cout << trash << std::endl;
                    punktNummer = std::atoi(trash.c_str());
                    sosiVertex[k].m_xyz[0] = punktNummer;
                    inn >> sosiVertex[k].m_xyz[1];
                    sosiVertex[k].m_xyz[0] /= 10000;
                    sosiVertex[k].m_xyz[2] /= 10000;
                    // std::cout << trash << std::endl;

                    if (sosiVertex[k].m_xyz[0] <= maxX && sosiVertex[k].m_xyz[0] >= minX && sosiVertex[k].m_xyz[1] <= maxY && sosiVertex[k].m_xyz[1] >= minY)
                    {
                        std::cout << "fant lengde bredde!" << std::endl;
                        std::cout << "Punkt " << k << " sin x = " << sosiVertex[k].m_xyz[0] << std::endl;
                        std::cout << "Punkt " << k << " sin y = " << sosiVertex[k].m_xyz[1] << std::endl;

                        sosiVertex[k].normal = QVector3D(0.0f,1.0f,0.0f);
                        sosiVertex[k].texCoord= QVector2D(0.0f,0.0f);
                        k++;

                            sosiVertex[k].m_xyz[1] = sosiVertex[k-1].m_xyz[1];

                        nyHoyde = false;
                    }
                    inn >> trash;
                    std::cout << trash << std::endl;
                    if (trash == ".SLUTT")
                    {
                        break;
                    }
                }

            }

        }
        std:: cout << "hva er k nå? : " << k <<". " << std::endl;

        antallPunkterInnenParameter = k;
        std::cout << antallPunkterInnenParameter << std::endl;
    }

    int mapSize = antallPunkterInnenParameter;

//    // Lukke fil
//    inn.close();
//    std::cout << "Filen er lest." << std::endl;
//    GLsizei  indexCount = mapSize * 2 * (mapSize-1) + (mapSize-2) * 2;
    GLushort *indices = new GLushort[mapSize];
//    int indexIndicies = 0;
//    for(int row = 0; row < mapSize; row++)
//    {
//       //make coloumns
//       for(int col = 0; col < (mapSize); col++)
//       {
//          indices[indexIndicies] = row * mapSize + col;
//          indexIndicies++;
//          indices[indexIndicies] = row * mapSize + col + mapSize;
//          indexIndicies++;
//       }
//       //make empty triangles before next row
//       if (row < (mapSize-2))
//       {
//          indices[indexIndicies] = indices[indexIndicies-1];
//          indexIndicies++;
//          indices[indexIndicies] = (row+1) * mapSize;
//          indexIndicies++;
//       }
//       if (indexIndicies == indexCount )
//         {
//          break;
//         }
//      }
//    for (int i =0; i <indexCount; i++)
//      {
//             // std::cout << "mMapData[" << i << "] = (" << mMapData[indices[i]].position[0] << ", " << mMapData[indices[i]].position[1] << ", " << mMapData[indices[i]].position[2] << ")" << std::endl;
//      }
    for(int i = 0; i < mapSize; i++)
     {
      indices[i] = i;
     }

    arrayBuf.create();
    indexBuf.create();
    arrayBuf.bind();
    // Transfer vertex data to VBO 0
    //arrayBuf.allocate(indices, 28 * sizeof(GLushort));
    arrayBuf.allocate(sosiVertex, mapSize * sizeof(VertexDataTrysil));
    indexBuf.bind();
    // Transfer index data to VBO 1
    indexBuf.allocate(indices, mapSize * sizeof(GLushort));
}

void trysil::drawTrysilGeometry(QOpenGLShaderProgram *program)
{
  // Tell OpenGL which VBOs to use

  indexBuf.bind();
  arrayBuf.bind();
  // Offset for position
  quintptr offset = 0;

  // Tell OpenGL programmable pipeline how to locate vertex position data
  int vertexLocation = program->attributeLocation("a_position");
  program->enableAttributeArray(vertexLocation);
  program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexDataTrysil));

  // Offset for texture coordinate
  offset += sizeof(QVector3D);

  // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
  int texcoordLocation = program->attributeLocation("a_texcoord");
  program->enableAttributeArray(texcoordLocation);
  program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexDataTrysil));

  // Offset for normals coordinate
  offset += sizeof(QVector2D);

  int normalLocation = program->attributeLocation("a_normal");
  program->enableAttributeArray(normalLocation);
  program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexDataTrysil));

   // qDebug() << vertexLocation << " " << texcoordLocation << " " << normalLocation;
  //Enables the light:
  //These first lines should be in an init-function
  m_lightPosUniform = program->uniformLocation("lightPosition");
  m_ambientColorUniform = program->uniformLocation("ambientColor");
  m_diffuseColorUniform = program->uniformLocation("diffuseColor");
  m_specularColorUniform = program->uniformLocation("specularColor");

  program->enableAttributeArray(m_lightPosUniform);
  program->enableAttributeArray(m_ambientColorUniform);
  program->enableAttributeArray(m_diffuseColorUniform);
  program->enableAttributeArray(m_specularColorUniform);

  program->setUniformValue(m_lightPosUniform, lightPos);
  //m_program->setUniformValue(m_ambientColorUniform, tempAmbient);
  program->setUniformValue(m_ambientColorUniform, ambientColor);
  program->setUniformValue(m_diffuseColorUniform, diffuseColor);
  program->setUniformValue(m_specularColorUniform, specularColor);


  // Draw cube geometry using indices from VBO 1
  glDrawElements(GL_LINE_STRIP, 354, GL_UNSIGNED_SHORT, 0);
  //glDrawElements(GL_TRIANGLE_STRIP, 32764, GL_UNSIGNED_SHORT, 0);

}


