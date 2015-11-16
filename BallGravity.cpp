#include "BallGravity.h"

BallGravity::BallGravity()
{

}

Vector3 BallGravity::getPosition() const
{
    return position;
}

Vector3 BallGravity::getVelocity() const
{
    return velocity;
}

Vector3 BallGravity::getAcceleration() const
{
    return acceleration;
}

Vector3 BallGravity::getAxis() const
{
    return axis;
}

void BallGravity::setPosition(const Vector3 &a)
{
    position = a;
}

void BallGravity::setVelocity(const Vector3 &a)
{
    velocity = a;
}

void BallGravity::setAcceleration(const Vector3 &a)
{
    acceleration = a;
}

void BallGravity::setAxis(const Vector3 &a)
{
    axis = a;
}

float BallGravity::getMass() const
{
    return mass;
}

void BallGravity::setMass(const float a)
{
    mass = a;
}

