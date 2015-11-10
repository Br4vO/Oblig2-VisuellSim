#ifndef TRANSFORM
#define TRANSFORM

#include <QVector3D>

/** Struct which holds position, rotation and scale
   */
struct Transform
{
    QVector3D mPosition;
    QVector3D mRotation;
    QVector3D mScale;

    Transform(){}
};

#endif // TRANSFORM

