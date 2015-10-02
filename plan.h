#ifndef PLAN_H
#define PLAN_H

#include "displayobject.h"

class Plan : public DisplayObject
{
private:
    GLuint m_tekstur;
public:
    Plan();
    ~Plan();
    virtual void initVertexBufferObjects();
    virtual void draw(GLint positionAttribute, GLint normalAttribute, GLint textureAttribute=-1);
    virtual void setTexture(GLuint texture);
};

#endif // PLAN_H
