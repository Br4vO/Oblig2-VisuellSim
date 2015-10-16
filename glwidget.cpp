/**
 * @file glwidget.cpp
 * @author Dag Nylund
 * @date 16.04.2013
 *
 *
 */
#include <QStatusBar>
#include <QMainWindow>
#include <QtGui/QOpenGLFunctions>
#include <QTimer>
#include <ctime>
#include <QPushButton>
#include "glwidget.h"
#include "mainWindow.h"
#include "displayobject.h"
#include "plan.h"
#include "shaderprogram.h"
#include "Texture.h"

/**
 * @brief GLWidget::GLWidget.
 * @param parent Peker til mainWindow
 *
 * Konstruktør som initierer @var m_parent og oppretter en timer
 */
GLWidget::GLWidget(MainWindow *parent) : QOpenGLWidget( parent),
    m_parent(parent),  m_frame(0), m_shaderProgramObjekt(0), QOpenGLFunctions()
{
    m_timer = new QTimer();
    //m_timer->start(17);
    //update() er ikke eget slot her - det er protected i QWidget
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));

    m_plan = new Plan();

    m_tid = new QTime(QTime::currentTime());
    m_tid->start();
}

// Dette er protected i QWidget
void GLWidget::update()
{
    QWidget::update();

    //Viser tiden
    //m_parent->statusBar()->showMessage(m_tid->currentTime().toString());

    // Beregner fps på en enkel måte
    int millisekunder = m_tid->elapsed();

    if (millisekunder % 1000 <=5)
    {
        QStatusBar* sb = m_parent->statusBar();
        sb->showMessage(QString::number(m_frame));
        m_frame = 0;
        //Det tar tid (mange frames) å restarte timeren
        //m_tid->restart();
    }

}
void GLWidget::repaint()
{
    //QWidget::repaint();
    qDebug() << "repaint";// << sender();
}
void GLWidget::paintEvent(QPaintEvent* event)
{
    QOpenGLWidget::paintEvent(event);
    //qDebug() << "paintEvent";
}

GLWidget::~GLWidget()
{
    delete m_plan;
}

/// property i QWidget klassen
QSize GLWidget::sizeHint() const
{
    return QSize(640, 480);
}

/**
 * brief blavla
 *
 * blabla
 * \param vvv
 * bla
 * \var var tetete
 */

void GLWidget::initializeGL()
{
    //f = QOpenGLContext::currentContext()->functions();
    initializeOpenGLFunctions();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_SAMPLER_2D);
    m_texture = new Texture("c:/glsl/130523/hund2.bmp");
    m_shaderProgramObjekt = new ShaderProgramObjekt();
    m_shaderProgramObjekt->initShader(m_parent->hentVertexShaderKode(), m_parent->hentFragmentShaderKode());

    m_positionAttribute = m_shaderProgramObjekt->getAttribLocation("aVertexPosition");
    m_colorAttribute = m_shaderProgramObjekt->getAttribLocation("aVertexColor");
    m_uniformMatrix = m_shaderProgramObjekt->getUniformLocation("uMatrix");
/// Tekstur i egen funksjon?
    m_textureAttribute = m_shaderProgramObjekt->getAttribLocation("aTextureCoordinates");
    m_uniformSampler = m_shaderProgramObjekt->getUniformLocation("uSampler");
qDebug() << "GLWidget initialize " << m_positionAttribute  << m_colorAttribute << m_textureAttribute;
    //m_tetraeder->initVertexBufferObjects();
    //m_xyz->initVertexBufferObjects();

    glEnable(GL_TEXTURE_2D);
    m_plan->setTexture(m_texture->id());
    m_plan->initVertexBufferObjects();

    glEnableVertexAttribArray(m_positionAttribute);
    glEnableVertexAttribArray(m_colorAttribute);
    glEnableVertexAttribArray(m_textureAttribute);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);

    //glEnable(GL_DOUBLEBUFFER); // default

    m_matrix.setToIdentity();
    qDebug() << "GLWidget::initializeGL() utført" ;

}

// Felles slot for alle pushbuttons i mainWindow
void GLWidget::klikket()
{
    QString navn = sender()->objectName();
    qDebug() << navn;
    if (navn == "start")
    {
        m_timer->start(17);
        sender()->setObjectName("stopp");
        QPushButton* qpb = dynamic_cast<QPushButton*>(sender());
        qpb->setText("stopp");
    }
    if (navn == "stopp")
    {
        m_timer->stop();
        sender()->setObjectName("start");
        QPushButton* qpb = dynamic_cast<QPushButton*>(sender());
        qpb->setText("start");
    }
    if (navn == "1")
    {
        initializeGL();
    }
}

void GLWidget::redigert()
{
    //qDebug() << "redigert";
    initializeGL();
}

/**
 * @brief GLWidget::initVertexBufferObjects
 *
 * Lager et tetraeder med fire punkter på unit ball og indekserer
 * for drawElements()
 * Arrayene er lokale, de trengs jo ikke når bufferdataene er laget
 */

void GLWidget::paintGL()
{
    // MouseMove i MainWindow genererer events som får paintGL() til
    // å utføres. Hindrer dette ved å teste om timeren går.

    if (!m_timer->isActive())
        return;

    m_shaderProgramObjekt->useProgram();

    glViewport(0, 0, width(), height());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_matrix.setToIdentity();
    m_matrix.perspective(60, 4.0/3.0, 0.1, 100.0);
    m_matrix.translate(0, 0, -2);

    // m er ordnet radvis, constData() returnerer kolonnevis
    // Vi må likevel sette transpose parameteren til GL_FALSE
    m_shaderProgramObjekt->setUniformMatrix(m_uniformMatrix, 1, GL_FALSE, m_matrix.constData());
    //m_xyz->draw(m_positionAttribute, m_colorAttribute);

    m_matrix.rotate(100.0f * m_frame / 60, 1, 1, 1);
    m_matrix.scale(0.5);
    m_shaderProgramObjekt->setUniformMatrix(m_uniformMatrix, 1, GL_FALSE, m_matrix.constData());

    //m_tetraeder->draw(m_positionAttribute, m_colorAttribute);//, m_textureAttribute);
    m_plan->draw(m_positionAttribute, m_colorAttribute, m_textureAttribute);

    ++m_frame; // brukes i update til å telle fps
}

void GLWidget::resizeGL(int width, int height)
{
    if (height == 0) height = 1;

    //m_matrix.setToIdentity();
    //m_matrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);

    glViewport(0, 0, width, height);
}

void GLWidget::mousePressEvent(QMouseEvent* event)
{

}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{

}

