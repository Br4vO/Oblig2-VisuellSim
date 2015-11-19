#ifndef VECTOR3_H
#define VECTOR3_H

///Way to simple vector3 class for soundsystem.
///This needs a lot of work to make it robust,
/// but should be kept fairly simpleand light weight.

class Vector3 {
    float x, y, z;
public:
    Vector3();
    Vector3(float _x, float _y, float _z);
//    void init(float _x, float _y, float _z);

//    float getX() const;
//    float getY() const;
//    float getZ() const;

//    void setX(const float _x);
//    void setY(const float _y);
//    void setZ(const float _z);

//    float dot(Vector3 a);

//    Vector3 operator -(const Vector3& a);

//    Vector3 operator *(const Vector3& a);

//    Vector3 operator *(float num);

//    Vector3 operator +(const Vector3& a);

//    Vector3 normalize();
};
#endif // VECTOR3_H
