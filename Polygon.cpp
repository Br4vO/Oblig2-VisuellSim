#include "Polygon.h"

Polygon::Polygon() {
    topleft.init(0.0, 0.0, 0.0);
    topright.init(0.0, 0.0, 0.0);
    botright.init(0.0, 0.0, 0.0);
}

void Polygon::PolygonVec(Vector3 _topleft, Vector3 _topright, Vector3 _botright) {
    topleft = _topleft;
    topright = _topright;
    botright = _botright;
}

Vector3 Polygon::getTopLeft() const
{
    return topleft;
}

Vector3 Polygon::getTopRight() const
{
    return topright;
}

Vector3 Polygon::getBotRight() const
{
    return botright;
}

void Polygon::setTopLeft(const Vector3 &_topleft)
{
    topleft = _topleft;
}

void Polygon::setTopRight(const Vector3 &_topright)
{
    topright = _topright;
}

void Polygon::setBotRight(const Vector3 &_botright)
{
    botright = _botright;
}
