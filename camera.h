#ifndef CAMERA_H
#define CAMERA_H

#include "geometryengine.h"
#include "mainwidget.h"

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class MainWidget;

class Camera
{
public:
  /// Initializer
  explicit Camera();
  /** Makes Camera
     Sets angle and viewroom for camera
     @param int and int - height and width
  */
  void cameraResizeGL(int, int);
  void rotate(float angle, const QVector3D &axis, QVector3D playerPos);
  void translate(QVector3D mTrans);
  ///Rotation to camera
  QQuaternion rotation;
  /// Camera projection
  QMatrix4x4 projection;
  QMatrix4x4 mViewMatrix;

protected:



};

#endif // CAMERA_H
