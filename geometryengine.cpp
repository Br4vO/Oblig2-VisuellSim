#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};

GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        // Vertex data for face 0 - front
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f),  QVector3D(0.0f, 0.0f,  1.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f), QVector3D(0.0f, 0.0f,  1.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f),  QVector3D(0.0f, 0.0f,  1.0f)}, // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f), QVector3D(0.0f, 0.0f,  1.0f)}, // v3

        // Vertex data for face 1 - right
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f), QVector3D(1.0f, 0.0f,  0.0f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f), QVector3D(1.0f, 0.0f,  0.0f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f),  QVector3D(1.0f, 0.0f,  0.0f)}, // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f), QVector3D(1.0f, 0.0f,  0.0f)}, // v7

        // Vertex data for face 2 - back
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f), QVector3D(0.0f, 0.0f,  -1.0f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f),  QVector3D(0.0f, 0.0f,  -1.0f)}, // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f), QVector3D(0.0f, 0.0f,  -1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f),  QVector3D(0.0f, 0.0f,  -1.0f)}, // v11

        // Vertex data for face 3 - left
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f), QVector3D(-1.0f, 0.0f,  0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f),  QVector3D(-1.0f, 0.0f,  0.0f)}, // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f), QVector3D(-1.0f, 0.0f,  0.0f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f),  QVector3D(-1.0f, 0.0f,  0.0f)}, // v15

        // Vertex data for face 4 - bottom
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f), QVector3D(0.0f, -1.0f,  0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f), QVector3D(0.0f, -1.0f,  0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f), QVector3D(0.0f, -1.0f,  0.0f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f), QVector3D(0.0f, -1.0f,  0.0f)}, // v19

        // Vertex data for face 5 - top
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f), QVector3D(0.0f, 1.0f,  0.0f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f), QVector3D(0.0f, 1.0f,  0.0f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f), QVector3D(0.0f, 1.0f,  0.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f), QVector3D(0.0f, 1.0f,  0.0f)}  // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));

}

void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Offset for normals coordinate
    offset += sizeof(QVector2D);

    int normalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    //Enables the light:
    //These first lines should be in an init-function
    m_lightPosUniform = program->uniformLocation("lightPosition");
    m_ambientColorUniform = program->uniformLocation("ambientColor");
    m_diffuseColorUniform = program->uniformLocation("diffuseColor");
    m_specularColorUniform = program->uniformLocation("specularColor");

    program->enableAttributeArray(m_lightPosUniform);
    program->enableAttributeArray(m_ambientColorUniform);
    program->enableAttributeArray(m_diffuseColorUniform);
    program->enableAttributeArray(m_specularColorUniform);

    program->setUniformValue(m_lightPosUniform, lightPos);
    //m_program->setUniformValue(m_ambientColorUniform, tempAmbient);
    program->setUniformValue(m_ambientColorUniform, ambientColor);
    program->setUniformValue(m_diffuseColorUniform, diffuseColor);
    program->setUniformValue(m_specularColorUniform, specularColor);

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
}
