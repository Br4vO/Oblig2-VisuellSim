#ifndef PLAN_H
#define PLAN_H

#include "displayobject.h"
#include "vertex.h"
#include "texture.h"

class Plan : public DisplayObject
{
private:
    //protected i DisplayObject
    //GLuint m_vertexBuffer;
    //GLuint m_colorBuffer;
    //GLuint m_indexBuffer;
    //GLuint m_textureBuffer;
    //GLuint m_tekstur;
    Vertex* m_vertices;
    Texture *m_texture;
    int m_antallVertices;
public:
    Plan();
    ~Plan();
    void lesfil(std::string filnavn);
    void data(float v[]) const;
    void initVertexBufferObjects();
    void draw(GLint positionAttribute, GLint normalAttribute, GLint textureAttribute=-1);

};

#endif // PLAN_H
