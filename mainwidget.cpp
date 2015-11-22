#include "mainwidget.h"
#include "camera.h"
#include "statemanager.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWidget>

#include "Vector3.h"

#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QGLWidget(parent),
    geometries(0),
    texture(0),
    angularSpeed(0)
{
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    destruct();
    doneCurrent();
}

void MainWidget::destruct()
{
    delete texture;
    delete geometries;
    delete manage;
    delete mCamera;
    //delete geometries;
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    if (manage->pause == false)
    {
        bulletFire = true;

        if (bulletCount < 4)
            bulletCount ++;


        for (int i = 0; i <3; i++)
        {
            if (bulletTravling[i] == false)
            {
                geometries->mKuler[i].mPosition = mBalls->ballTransform.mPosition;
                bulletTravling[i] = true;
                i = 3;
            }
        }
        // Save mouse press position
        mousePressPosition = QVector2D(e->localPos());

    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (manage->pause == false)
    {
        // Mouse release position - mouse press position
        QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

        // Rotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

        // Accelerate angular speed relative to the length of the mouse sweep
        qreal acc = diff.length() / 100.0;

        // Calculate new rotation axis as weighted sum
        rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

        // Increase angular speed
        angularSpeed += acc;
    }
}

void MainWidget::keyPressEvent(QKeyEvent *e)
{
    if (manage->pause == false)
    {
        if (e->key() == Qt::Key_A)
        {
            //mBalls->ballTransform.mPosition += QVector3D(0.1f,0.0f,0.0f);
            buttonADown = true;
        }
        if (e->key() == Qt::Key_S)
        {
            //mBalls->ballTransform.mPosition += QVector3D(0.1f,0.0f,0.0f);
            buttonSDown = true;
        }
        if (e->key() == Qt::Key_D)
        {
            //mBalls->ballTransform.mPosition += QVector3D(0.1f,0.0f,0.0f);
            buttonDDown = true;
        }
        if (e->key() == Qt::Key_W)
        {
            //mBalls->ballTransform.mPosition += QVector3D(0.1f,0.0f,0.0f);
            buttonWDown = true;
        }

        if (e->key() == Qt::Key_M)
        {
            if (farMode == false)
            {
                mCamera->mViewMatrix.translate(QVector3D(0.0f, 1.0f, 2.0f));
                farMode = true;
            }
            else
            {
                mCamera->mViewMatrix.translate(QVector3D(0.0f, -1.0f, -2.0f));
                farMode = false;
            }
        }

        if(e->key() == Qt::Key_J)
        {
            mCamera->rotate(4.0, QVector3D(0.0,1.0,0.0), mBalls->ballTransform.mPosition);
        }
        if(e->key() == Qt::Key_L)
        {
            mCamera->rotate(-4.0, QVector3D(0.0,1.0,0.0), mBalls->ballTransform.mPosition);
        }
        if(e->key() == Qt::Key_I)
        {
            mCamera->rotate(4.0, QVector3D(1.0,0.0,0.0), mBalls->ballTransform.mPosition);
        }
        if(e->key() == Qt::Key_K)
        {
            mCamera->rotate(-4.0, QVector3D(1.0,0.0,0.0), mBalls->ballTransform.mPosition);
        }
        if(e->key() == Qt::Key_U)
        {
            mCamera->rotate(4.0, QVector3D(0.0,0.0,1.0), mBalls->ballTransform.mPosition);
        }
        if(e->key() == Qt::Key_O)
        {
            mCamera->rotate(-4.0, QVector3D(0.0,0.0,1.0), mBalls->ballTransform.mPosition);
        }

    }
    if (e->key() == Qt::Key_Space)
    {
        manage->pauseProgram();
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_A)
    {
        buttonADown = false;
    }
    if (e->key() == Qt::Key_S)
    {
        buttonSDown = false;
    }
    if (e->key() == Qt::Key_D)
    {
        buttonDDown = false;
    }
    if (e->key() == Qt::Key_W)
    {
        buttonWDown = false;
    }
}

void MainWidget::timerEvent(QTimerEvent *)
{
    gameLoop();
}

void MainWidget::gameLoop()
{ 
    if (manage->pause == false)
    {
        //Process Input
        // Decrease angular speed (friction)
        angularSpeed *= 0.99;

        // Stop rotation when speed goes below threshold
        if (angularSpeed < 0.01)
        {
            angularSpeed = 0.0;
        }
        else
        {
            // Update rotation
            mCamera->rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * mCamera->rotation;
            //mCamera->mViewMatrix.rotate(mCamera->rotation);
        }
        //Renders if rotation is changed.
        updateMovement();
        //updateHitdetection();
        update();
    }

}

void MainWidget::updateMovement()
{
    float speed = 0.5;
    if ( buttonADown == true)
    {
        mBalls->ballTransform.mPosition += QVector3D(-speed,0.0f,0.0f);
        mCamera->mViewMatrix.translate(QVector3D(speed,0.0f,0.0f));
    }
    if (buttonSDown == true)
    {
        mBalls->ballTransform.mPosition += QVector3D(0.0f, 0.0f,-speed);
        mCamera->mViewMatrix.translate(QVector3D(0.0f, 0.0f,speed));
    }
    if (buttonDDown == true)
    {
        mBalls->ballTransform.mPosition += QVector3D(speed,0.0f,0.0f);
        mCamera->mViewMatrix.translate(QVector3D(-speed,0.0f,0.0f));
    }
    if (buttonWDown == true)
    {
        mBalls->ballTransform.mPosition += QVector3D(0.0f,0.0f,speed);
        mCamera->mViewMatrix.translate(QVector3D(0.0f,0.0f,-speed));
    }

    mCamera->mViewMatrix.translate(mBalls->updateBall());

    //    for (int i = 0; i < geometries->antallFiender; i ++)
    //    {
    //        geometries->mFiender[i].mPosition += QVector3D(0.0f,-0.001f,0.0f);
    //    }
}

void MainWidget::updateHitdetection()
{
    //    for (int i =0; i < 3; i++)
    //    {
    //        for (int j = 0; j < geometries->antallFiender; j++)
    //        {
    //            if (bulletCount > 0)
    //            {
    //                if (geometries->mFiender[j].mPosition.distanceToPoint(geometries->mKuler[i].mPosition) <= 0.5)
    //                {
    //                    geometries->mKuler[i].mPosition = mBalls->ballTransform.mPosition;
    //                    geometries->mFiender[j].mPosition += QVector3D(0.0f, 50.0f,0.0f);
    //                    bulletCount --;
    //                    bulletTravling[i] = false;
    //                }
    //            }
    //            if (geometries->mFiender[j].mPosition.distanceToPoint(mBalls->ballTransform.mPosition) <= 0.5f)
    //            {
    //                mBalls->ballTransform.mPosition += QVector3D(0.0f, 50.0f,0.0f);
    //            }
    //        }
    //    }
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.3, 0.3, 0.3, 1);

    makeCurrent();
    mCamera = new Camera;
    manage = new stateManager;
    geometries = new GeometryEngine(64.0, -23.75, 64);
    map = new HeightMap;
    cube = new cubemaker;
    mGround = new GroundHeight;
    mTrysil = new trysil;
    mBalls = new Balls(64.0, -23.75, 64);

    initShaders();
    initTextures();

    mCamera->translate(mBalls->ballTransform.mPosition);
    mCamera->mViewMatrix.translate(QVector3D(-35.0f,-20.8f,-65.0f));
    mCamera->rotate(180.0, QVector3D(0.0,0.0,1.0),QVector3D(0.0, 0.0, 0.0));
    mCamera->rotate(180.0, QVector3D(0.0,1.0,0.0),QVector3D(0.0, 0.0, 0.0));
    mCamera->rotate(45.0, QVector3D(1.0,0.0,0.0),QVector3D(0.0, 0.0, 0.0));

    mBalls->createBall();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void MainWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
    // Load cube.png image
    texturePlane = new QOpenGLTexture(QImage(":/grid.bmp"));

    // Set nearest filtering mode for texture minification
    texturePlane->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texturePlane->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texturePlane->setWrapMode(QOpenGLTexture::Repeat);
}

void MainWidget::resizeGL(int w, int h)
{

    mCamera->cameraResizeGL(w, h);
}

void MainWidget::paintGL()
{
    //Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texturePlane->bind();
    QMatrix4x4 matrix1;
    matrix1.setToIdentity();

    // Set projection matrix
    program.setUniformValue("pMatrix", mCamera->projection);

    // Set modelview matrix
    QMatrix4x4 mvMatrix = mCamera->mViewMatrix*matrix1;
    program.setUniformValue("mvMatrix", mvMatrix);

    // Set nMatrix
    //matrix for normals - inverted mv-matrix
    QMatrix3x3 nMatrix = matrix1.normalMatrix();
    //hooking matrix to shader
    program.setUniformValue("nMatrix", nMatrix);

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);
    // Draw cube geometry
    map->drawPlaneGeometry(&program);

    ///////WE DRAW ALL OF THE BALLS
    texture->bind();
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.translate(mBalls->ballTransform.mPosition);
    matrix.rotate(mBalls->m_tetaX, 1, 0, 0);
    matrix.rotate(mBalls->m_tetaY, 0, 1, 0);
    matrix.rotate(mBalls->m_tetaZ, 0, 0, 1);
   // matrix.scale(mBalls->ballTransform.mScale);

    // Set projection matrix
    program.setUniformValue("pMatrix", mCamera->projection);

    // Set modelview matrix
    mvMatrix = mCamera->mViewMatrix*matrix;
    program.setUniformValue("mvMatrix", mvMatrix);

    // Set nMatrix
    //matrix for normals - inverted mv-matrix
    nMatrix = matrix.normalMatrix();
    //hooking matrix to shader
    program.setUniformValue("nMatrix", nMatrix);

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);
    // Draw cube geometry
    mBalls->drawBall(&program);
}
