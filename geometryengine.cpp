#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>


GeometryEngine::GeometryEngine(float x, float y, float z)
{
//    cuMa = new cubemaker();
//    heMap = new HeightMap();
    initializeOpenGLFunctions();

    //Making player position and scale.
    mTrans.mPosition = QVector3D(x,y,z);
    mTrans.mScale = QVector3D(1.0f, 1.0f, 1.0f);

    // Initializes cube geometry and transfers it to VBOs
    //initAmmoGeometry();
    //initEnemyGeometry();
    initCubeGeometry();
    initMapGeometry();


}

GeometryEngine::~GeometryEngine()
{
}

void GeometryEngine::initAmmoGeometry()
{
  for (int i = 0; i < 3; i ++)
    {
      mKuler[i].mPosition = mTrans.mPosition;
      mKuler[i].mScale = QVector3D(0.01f, 0.3f, 0.01f);
    }
}

void GeometryEngine::initEnemyGeometry()
{
  int k = 0;

  for(float i = -2.0f; i < 2.0f; i += 0.5f)
    {
      mFiender[k].mPosition = QVector3D(i, 2.0f, -5.0f);
      mFiender[k].mScale = QVector3D(0.2f,0.2f,0.2f);
      k ++;
    }
}
void GeometryEngine::initCubeGeometry()
{


    //cuMa->makeCubePls(arrayBuf, indexBuf);
}

void GeometryEngine::initMapGeometry()
{
  //heMap->HeightMap();
}
