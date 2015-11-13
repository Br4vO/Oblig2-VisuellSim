#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "geometryengine.h"
#include "statemanager.h"
#include "camera.h"
#include "transform.h"
#include "cubemaker.h"
#include "heightmap.h"
#include "GroundHeight.h"
#include "trysil.h"
#include "balls.h"

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QKeyEvent>

class Balls;
/// Makes camera class for use in mainwidget
class Camera;
/// Makes statemanager class for use in mainwidget
class stateManager;
/// Makes GeometryEngine class for use in mainwidget
class GeometryEngine;
class cubemaker;
class HeightMap;
class GroundHeight;
class trysil;
/// Mainwidget uses QGLwidget and QOpenGLFunctions functions.
class MainWidget : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
  /** Initalizer.
     Makes class pointers and initates other classes
     @param parent - Something from QWidget class which has something to do with rendering
     */
    explicit MainWidget(QWidget *parent = 0);
  /** Destructor.
     Deletes all classes that was initialized in this class
     */
    ~MainWidget();
    /// Tekstur variabel
    QOpenGLTexture *texture;
    QOpenGLTexture *texturePlane;
    /// Timer som funker som update funksjon
    QBasicTimer timer;
    /// Shader program
    QOpenGLShaderProgram program;
    /// Peker til geometries class
    GeometryEngine *geometries;
    cubemaker *cube;
    HeightMap *map;
    GroundHeight *mGround;
    trysil *mTrysil;
    /// Peker til camera class
    Camera *mCamera;
    /// Peker til statemanger
    stateManager *manage;
    ///Pointer to the Balls class
    Balls *mBalls;
    /// Makes transform which hold data for player
    Transform trans;
    /// Position mousebutton was pressed
    QVector2D mousePressPosition;
    /// Axis which the camera rotates
    QVector3D rotationAxis;
    /// Speed which camera rotates
    qreal angularSpeed;
    /// Matrix which is used to move and transform objects
    QMatrix4x4 matrix;
    /// Counts bullets which is shot
    int bulletCount = 0;

protected:
    /** Deletes pointers and classes created.
       */
    void destruct();
    /** Event for when mousebutton is pressed.
       Fires bullet when mouse clicked
       */
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    /** Event for when mousebutton is released.
       Does nothing
       */
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    /** Event for when key is pressed
       Controlls player with WASD
       */
    void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;
    /** Event for when key is released.
       Player stops moving when button is released.
       */
    void keyReleaseEvent(QKeyEvent *e) Q_DECL_OVERRIDE;
    /** Timer which works as updating funktion.
       */
    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;
    /** Holds the gameloop with all its funtions.
       */
    void gameLoop();
    /** Moves objects.
       Updates movement on enemies and bullets and player.
       */
    void updateMovement();
    /** Checks if things hit each other.
       Bullet hit enemy, player hit enemy
       */
    void updateHitdetection();
    /** Initializes OpenGlFunctions.
       Also; makes shader and textures and skybox color
       */
    void initializeGL() Q_DECL_OVERRIDE;
    /** Sends screen size to camera.
       */
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    /** Makes matrix for objects and sends it to shader.
       Then sends shader to geometry engine which draws
       */
    void paintGL() Q_DECL_OVERRIDE;
    /** Makes shader
       */
    void initShaders();
    /** Makes textures
       */
    void initTextures();

private:
    /// Checks if buttons are pressed down
    bool buttonADown = false;
    bool buttonSDown = false;
    bool buttonDDown = false;
    bool buttonWDown = false;
    bool farMode = false;
    /// Checks if bullets are fired
    bool bulletFire = false;
    /// Checks which bullets are travling
    bool bulletTravling[3] = {false, false, false};
    QMatrix4x4 matrix1;
        QMatrix4x4 viewMatrix;
};

#endif // MAINWIDGET_H
