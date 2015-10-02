#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QMatrix4x4>
#include <QtGui/QScreen>
#include <QOpenGLFunctions>
#include <QTime>

class MainWindow;
class DisplayObject;
class ShaderProgramObjekt;
class Texture;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(MainWindow *parent = 0);
    ~GLWidget();

signals:

public slots:

    void klikket();
    void redigert();
    //ikke lag eget slot her - det er protected i QWidget
    void update();
    void repaint();
    //void initializeShader();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
private:
    QSize sizeHint() const;
    ShaderProgramObjekt* m_shaderProgramObjekt; // Erstatter QOpenGLShaderProgram* m_program;
    QMatrix4x4 m_matrix;
    /// Disse hentes ut fra shaderen
    GLuint m_positionAttribute;
    GLuint m_colorAttribute;
    GLuint m_uniformMatrix;

    GLint m_textureAttribute;
    GLint m_uniformSampler;

    //GLint m_texture;

    int m_frame;
    QTimer* m_timer;

    MainWindow* m_parent;
    DisplayObject* m_tetraeder;
    DisplayObject* m_xyz;
    DisplayObject* m_plan;

    QOpenGLContext* m_context;
    QSurface* m_surface;
    QTime* m_tid;
    Texture* m_texture;
    //QOpenGLFunctions* f;
};

#endif // GLWIDGET_H
