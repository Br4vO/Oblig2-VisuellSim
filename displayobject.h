#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <QtGui>
#include <QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>

class DisplayObject : protected QOpenGLFunctions
{
public:
    DisplayObject();
    //DisplayObject(QOpenGLFunctions* fp);
    virtual ~DisplayObject();
    virtual void initVertexBufferObjects() = 0;
    virtual void draw(GLint positionAttribute, GLint colorAttribute, GLint textureAttribute=-1) = 0 ;
    virtual void setTexture(GLuint texture) {} /// reimplementeres for klasser med tekstur
protected:
    GLuint m_vertexBuffer;
    GLuint m_normalBuffer;
    GLuint m_indexBuffer;
    GLuint m_textureBuffer;
};

#endif // DISPLAYOBJECT_H
