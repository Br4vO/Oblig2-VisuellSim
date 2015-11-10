#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include "cubemaker.h"
#include "transform.h"
#include "heightmap.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

/////Makes cubemaker so it can be used in GeometryEngine
//class cubemaker;
/////Makes heightmap so it can be used in GeometryEngine
//class HeightMap;

/// Class GeometryEngine which uses QOpenGLFunctions
class GeometryEngine : protected QOpenGLFunctions
{
public:
    /** Initializes arraybuffers and transform for objects.
       @param x - x-coord for player-cube
       @param y - y-coord for player-cube
       @param z - z-coord for player-cube
      */
    GeometryEngine(float x, float y, float z);
    /** destructor.
       Deletes Buffers when finished
       */
    virtual ~GeometryEngine();
    /** Sends inn all of data to shaderprogram.
       It sends inn vertexdata, lighting and texture
       @param program - Shader program
      */
    void drawCubeGeometry(QOpenGLShaderProgram *program);
    void drawPlaneGeometry(QOpenGLShaderProgram *program);

//    ///Pointer to cubemaker class
//    cubemaker *cuMa;
//    ///Pointer to heightmap class
//    HeightMap *heMap;
   /// Transform which holds player position, rotation and scale.
   Transform mTrans;
   /// Transform array which holds enemy position, rotation and scale.
   Transform mFiender[10];
   int antallFiender = 10;
   /// Transform array which holds bullets position, rotation and scale.
   Transform mKuler[3];

private:
   /** Makes transform data for bullets.
      Sets bullet position to player position and scales it to have the shape of a bullet
      */
   void initAmmoGeometry();
   /** Makes transform data for enemies.
      Sets enemy position to top of the screen and scales them a bit
      */
   void initEnemyGeometry();
   /** Retrives vertex and indices data from cubemaker class.
      Also binds buffers
      */
    void initCubeGeometry();
    /** Retrives vertex and indices data for heightmap.
       Also binds buffers */
    void initMapGeometry();

//    /// Array buffer for vertex data for cube.
//    QOpenGLBuffer arrayBuf;
//    /// Index buffer for indices data for cube.
//    QOpenGLBuffer indexBuf;
};

#endif // GEOMETRYENGINE_H
