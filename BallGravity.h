#ifndef BALLGRAVITY_H
#define BALLGRAVITY_H

#include "Vector3.h"

class Vector3;

class BallGravity
{
public:
    BallGravity();
    Vector3 getPosition() const;
    Vector3 getVelocity() const;
    Vector3 getAcceleration() const;
    Vector3 getAxis() const;

    void setPosition(const Vector3& a);
    void setVelocity(const Vector3& a);
    void setAcceleration(const Vector3& a);
    void setAxis(const Vector3& a);

    float getMass() const;
    void setMass(const float a);

private:
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    Vector3 axis;
    float mass;
    float bodyrot;
};

#endif // BALLGRAVITY_H
