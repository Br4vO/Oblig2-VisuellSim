#include "camera.h"

Camera::Camera()
{
}

void Camera::cameraResizeGL(int we, int he)
{
  // Calculate aspect ratio
  qreal aspect = qreal(we) / qreal(he ? he : 1);
  // Set near plane to 0.1, far plane to 1000.0, field of view 45 degrees
  const qreal zNear = 0.1, zFar = 1000.0, fov = 45.0;

  // Reset projection
  projection.setToIdentity();

  // Set perspective projection
  projection.perspective(fov, aspect, zNear, zFar);
}
void Camera::rotate(float angle, const QVector3D &axis)
{
  mViewMatrix.rotate(angle, axis);
}

void Camera::translate(QVector3D mTrans)
{
  QMatrix4x4 temp;
  mTrans += QVector3D(-93.0f,-20.0f,0.5f);
  temp.translate(mTrans);
  mViewMatrix = temp;
}
