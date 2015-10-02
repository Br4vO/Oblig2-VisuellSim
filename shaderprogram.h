#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QOpenGLFunctions>
#include <QString>

class ShaderProgramObjekt : protected QOpenGLFunctions
{
private:
    GLuint m_shaderProgramObjekt;
    GLuint shader(GLenum shaderType, const QString& kildeKode);

public:
    ShaderProgramObjekt();
    void initShader(const QString& vertexKode, const QString& fragmentKode);
    GLint getAttribLocation(const GLchar* name);
    GLint getUniformLocation(const GLchar* name);
    void setUniformMatrix(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    void useProgram();
};

#endif // SHADERPROGRAM_H
