#include "vector3.h"




Vector3::Vector3()
{
    x=0;
    y=0;
    x=0;
}

Vector3::Vector3(float _x, float _y, float _z)
{
    x=_x;
    y=_y;
    z=_z;
}



void Vector3::init(float _x, float _y, float _z)
{
    x=_x;
    y=_y;
    z=_z;
}

float Vector3::getX() const
{
    return x;
}

float Vector3::getY() const
{
    return y;
}

float Vector3::getZ() const
{
    return z;
}

void Vector3::setX(const float _x)
{
    x = _x;
}

void Vector3::setY(const float _y)
{
    y = _y;
}

void Vector3::setZ(const float _z)
{
    z = _z;
}

float Vector3::dot(Vector3 a)
{
    return( x * a.getX() + y * a.getY() + z * a.getZ() );
}

Vector3 Vector3::operator -(const Vector3 &a) {
    Vector3 temp;
    temp.x = x - a.x;
    temp.y = y - a.y;
    temp.z = z - a.z;
    return temp;
}

Vector3 Vector3::operator *(const Vector3 &a) {
    Vector3 cross;
    cross.x = y * a.z - z * a.y;
    cross.y = z * a.x - x * a.z;
    cross.z = x * a.y - y * a.x;
    return cross;
}

Vector3 Vector3::operator *(const Vector3 &a) {
    Vector3 cross;
    cross.x = y * a.z - z * a.y;
    cross.y = z * a.x - x * a.z;
    cross.z = x * a.y - y * a.x;
    return cross;
}

Vector3 Vector3::operator *(float num) {
    Vector3 result;
    result.x = x * num;
    result.y = y * num;
    result.z = z * num;
    return result;
}

Vector3 Vector3::operator +(const Vector3 &a) {
    Vector3 sum;
    sum.x = x + a.x;
    sum.y = y + a.y;
    sum.z = z + a.z;
    return sum;
}

Vector3 Vector3::normalize() {
    float mag = sqrtf(x * x + y * y + z * z);
    x /= mag;
    y /= mag;
    z /= mag;
    Vector3 vec(x,y,z);
    return vec;
}
