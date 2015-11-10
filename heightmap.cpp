#include "heightmap.h"
#include "geometryengine.h"
#include <QImage>
#include <QDebug>
#include <QColor>

HeightMap::HeightMap() : indexBuf(QOpenGLBuffer::IndexBuffer)
{
  initializeOpenGLFunctions();
  readHeightMap();
}

void HeightMap::readHeightMap()
{
  QImage* image = new QImage("D://Spillmotorarkitektur//ORF_2015//heightmap.bmp");
  //std::cout << "heightmap is nonexcisting = " << image->isNull() << std::endl;
  int width = image->width();
    std::cout << "width = " << width << std::endl;
  int height = image->height();
    std::cout << "height = " << height << std::endl;
  int mapSize = width;

  for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
        {
          QRgb *color = new QRgb(image->pixel(i,j));
          int redColor = qRed(*color);
          //std::cout << "Red = " << redColor << std::endl;
          mMapData[(width*i)+j].position = QVector3D(i/1.0f-0.64f,2.55-(redColor/100.0f),j/1.0f-0.64f);
          mMapData[(width*i)+j].normal = QVector3D(float(j)/height, float(i)/height,  (10.0f+j)/8);
          //mMapData[(width*i)+j].normal = QVector3D(1, 0, 1);
          //std::cout << "MapData" << (width*i)+j << "(x,y,z) = (" << i/100.0f << ", " << redColor/1000.0f << ", " << j/100.0f << ")" << std::endl;
          mMapData[(width*i)+j].texCoord = QVector2D(1.0f/128.0f*i,1.0f/128.0f*j);
        }
    }

  GLsizei  indexCount = mapSize * 2 * (mapSize-1) + (mapSize-2) * 2;
  GLushort *indices = new GLushort[indexCount];
  int indexIndicies = 0;
  for(int row = 0; row < mapSize; row++)
  {
     //make coloumns
     for(int col = 0; col < (mapSize); col++)
     {
        indices[indexIndicies] = row * mapSize + col;
        indexIndicies++;
        indices[indexIndicies] = row * mapSize + col + mapSize;
        indexIndicies++;
     }
     //make empty triangles before next row
     if (row < (mapSize-2))
     {
        indices[indexIndicies] = indices[indexIndicies-1];
        indexIndicies++;
        indices[indexIndicies] = (row+1) * mapSize;
        indexIndicies++;
     }
     if (indexIndicies == indexCount )
       {
        break;
       }
    }
  for (int i =0; i <indexCount; i++)
    {
           // std::cout << "mMapData[" << i << "] = (" << mMapData[indices[i]].position[0] << ", " << mMapData[indices[i]].position[1] << ", " << mMapData[indices[i]].position[2] << ")" << std::endl;
    }

  arrayBuf.create();
  indexBuf.create();
  arrayBuf.bind();
  // Transfer vertex data to VBO 0
  //arrayBuf.allocate(indices, 28 * sizeof(GLushort));
  arrayBuf.allocate(mMapData, mapSize*mapSize * sizeof(VertexDataLOL));
  indexBuf.bind();
  // Transfer index data to VBO 1
  indexBuf.allocate(indices, indexCount * sizeof(GLushort));
}

QVector3D HeightMap::normal(QVector3D P1, QVector3D P2, QVector3D P3)
{
  QVector3D a = P1.normal(P2,P3);
  return a;
}


void HeightMap::drawPlaneGeometry(QOpenGLShaderProgram *program)
{
  // Tell OpenGL which VBOs to use

  indexBuf.bind();
  arrayBuf.bind();
  // Offset for position
  quintptr offset = 0;

  // Tell OpenGL programmable pipeline how to locate vertex position data
  int vertexLocation = program->attributeLocation("a_position");
  program->enableAttributeArray(vertexLocation);
  program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexDataLOL));

  // Offset for texture coordinate
  offset += sizeof(QVector3D);

  // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
  int texcoordLocation = program->attributeLocation("a_texcoord");
  program->enableAttributeArray(texcoordLocation);
  program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexDataLOL));

  // Offset for normals coordinate
  offset += sizeof(QVector2D);

  int normalLocation = program->attributeLocation("a_normal");
  program->enableAttributeArray(normalLocation);
  program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexDataLOL));

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
  //glDrawElements(GL_LINE_STRIP, 32764, GL_UNSIGNED_SHORT, 0);
  glDrawElements(GL_TRIANGLE_STRIP, 32764, GL_UNSIGNED_SHORT, 0);

}

