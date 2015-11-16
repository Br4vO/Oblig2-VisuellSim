#ifndef POLYGON_H
#define POLYGON_H

#include "vector3.h"

class Polygon {
    Vector3 topleft;
    Vector3 topright;
    Vector3 botright;
public:
    Polygon();

    void PolygonVec(Vector3 _topleft, Vector3 _topright, Vector3 _botright );

    Vector3 getTopLeft() const;
    Vector3 getTopRight() const;
    Vector3 getBotRight() const;

    void setTopLeft(const Vector3& _topleft);
    void setTopRight(const Vector3& _topright);
    void setBotRight(const Vector3& _botright);

#endif // POLYGON_H
