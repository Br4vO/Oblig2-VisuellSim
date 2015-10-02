#include "displayobject.h"

DisplayObject::DisplayObject() : QOpenGLFunctions(),
    m_vertexBuffer(0), m_normalBuffer(0), m_indexBuffer(0), m_textureBuffer(0)
{
}

DisplayObject::~DisplayObject()
{
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteBuffers(1, &m_normalBuffer);
    glDeleteBuffers(1, &m_indexBuffer);
    glDeleteBuffers(1, &m_textureBuffer);
}

//void DisplayObject::setTexture(GLuint /*texture*/)
//{
    // reimplementeres for klasser med tekstur
//}
