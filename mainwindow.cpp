#include <QtWidgets>
#include "mainWindow.h"
#include "glwidget.h"
#include "shaderprogram.h"

MainWindow::MainWindow() : QMainWindow()
{
    createMenu();

    fragmentShaderFilnavn = new QString("fragmentshader.glsl");
    vertexShaderFilnavn = new QString("vertexshader.glsl");

    fragmentShaderEditor = new QTextEdit();
    // Dette gir en uønsket ekstra, liten scrollbar øverst til venstre:
    // QScrollBar* fragmentVScrollBar = new QScrollBar(Qt::Vertical, fragmentShaderEditor);
    QScrollBar* fragmentVScrollBar = new QScrollBar(Qt::Vertical);
    fragmentShaderEditor->addScrollBarWidget(fragmentVScrollBar, Qt::AlignRight);

    QString tekst;
    loadFile(*fragmentShaderFilnavn, tekst);
    fragmentShaderEditor->setPlainText(tekst);

    vertexShaderEditor = new QTextEdit();
    QScrollBar* vertexVScrollBar = new QScrollBar(Qt::Vertical);
    vertexShaderEditor->addScrollBarWidget(vertexVScrollBar, Qt::AlignRight);
    loadFile(*vertexShaderFilnavn, tekst);
    vertexShaderEditor->setPlainText(tekst);

    glWidget = new GLWidget(this);


    QLayout* knapper = buttonLayout();

    m_hBoxLayout = new QHBoxLayout();
    m_hBoxLayout->addLayout(knapper);
    m_hBoxLayout->addWidget(glWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    setMenuWidget(menuBar);

    mainLayout->addWidget(fragmentShaderEditor);
    mainLayout->addWidget(vertexShaderEditor);
    mainLayout->addLayout(m_hBoxLayout);

    QWidget* mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    //mainLayout->addWidget(glWidget);
    //mainLayout->addWidget(bigEditor);

    //setLayout(mainLayout);
    setWindowTitle(tr("Basic OpenGL"));
    statusBar()->showMessage("Hei Marianne!");

    kobleSignalsAndSlots();
    //ShaderProgram sh(vertexShaderEditor->toPlainText(), fragmentShaderEditor->toPlainText());
}

void MainWindow::kobleSignalsAndSlots()
{
    /// QPushButton klassen har signalet clicked()
    /// Kobler alle knappenes clicked() til samme slot klikket() i glWidget
    for (int i=0; i<NumButtons; i++)
        connect(buttons[i],SIGNAL(clicked()), glWidget, SLOT(klikket()));

    /// QAction klassen har signalet triggered()
    /// Kobler disse til respektive slot for å lese/skrive shaderkode fra fil
    connect(openFragmentAction, SIGNAL(triggered()), this, SLOT(openFragmentShader()));
    connect(openVertexAction, SIGNAL(triggered()), this, SLOT(openVertexShader()));
    connect(saveFragmentAction, SIGNAL(triggered()), this, SLOT(saveFragmentShader()));
    connect(saveVertexAction, SIGNAL(triggered()), this, SLOT(saveVertexShader()));

    /// Kobler også disse til samme slot redigert() i glWidget - litt misvisende navn
    connect(openFragmentAction, SIGNAL(triggered()), this, SLOT(redigert()));
    connect(openVertexAction, SIGNAL(triggered()), this, SLOT(redigert()));
    connect(saveFragmentAction, SIGNAL(triggered()), this, SLOT(redigert()));
    connect(saveVertexAction, SIGNAL(triggered()), this, SLOT(redigert()));

    // close() er et slot i QWidget
    // For sikrere exit: Angi som eget slot her, og reimplementer med QWidget::close()
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

QString MainWindow::hentFragmentShaderFilnavn() const { return *fragmentShaderFilnavn; }
QString MainWindow::hentVertexShaderFilnavn() const  { return *vertexShaderFilnavn; }
QString MainWindow::hentFragmentShaderKode() const { return fragmentShaderEditor->toPlainText(); }
QString MainWindow::hentVertexShaderKode() const { return vertexShaderEditor->toPlainText() ; }

/// Lager et button layout med navn på knapper for bruk i glWidget slot
QLayout* MainWindow::buttonLayout()
{
    /*
    QVBoxLayout* vBoxLayout = new QVBoxLayout();
    for (int i = 0; i < NumButtons; ++i)
    {
        buttons[i] = new QPushButton(tr("Button %1").arg(i + 1));
        vBoxLayout->addWidget(buttons[i]);
    }

    return vBoxLayout;
    */
    QGridLayout* gridLayout = new QGridLayout();
    for (int i = 0; i < 5; ++i)
    {
        QString qs(tr("%1").arg(i + 1));
        buttons[i] = new QPushButton(qs);
        buttons[i]->setFixedWidth(30);
        buttons[i]->setObjectName(qs);
    }

    buttons[5] = new QPushButton("start");
    buttons[5]->setObjectName("start");
    //buttons[6] = new QPushButton("stopp");
    //buttons[6]->setObjectName("stopp");


    for (int i = 6; i < NumButtons; ++i)
    {
        QString qs(tr("%1").arg(i + 1));
        buttons[i] = new QPushButton(qs);
        buttons[i]->setObjectName(qs);

    }
    gridLayout->addWidget(buttons[0], 0, 1);
    gridLayout->addWidget(buttons[1], 1, 0);
    gridLayout->addWidget(buttons[2], 1, 1);
    gridLayout->addWidget(buttons[3], 1, 2);
    gridLayout->addWidget(buttons[4], 2, 1);
    for (int i=5; i<NumButtons; i++)
         gridLayout->addWidget(buttons[i], i-3, 0, 3, 0);
    return gridLayout;
}

void MainWindow::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    openFragmentAction = fileMenu->addAction(tr("Open F&ragment..."));
    openVertexAction = fileMenu->addAction(tr("Open &Vertex..."));
    saveFragmentAction = fileMenu->addAction(tr("Save Fragment..."));
    saveVertexAction = fileMenu->addAction(tr("Save Vertex..."));
    menuBar->addSeparator();
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);
}

void MainWindow::openFragmentShader()
{
    qDebug() << "frag";
    QString filnavn = QFileDialog::getOpenFileName(this);
     if (!filnavn.isEmpty())
     {
         QString tekst;
         loadFile(filnavn, tekst);
         fragmentShaderEditor->setPlainText(tekst);
     }

}

void MainWindow::openVertexShader()
{
    QString filnavn = QFileDialog::getOpenFileName(this);
    if (!filnavn.isEmpty())
    {
        QString tekst;
        loadFile(filnavn, tekst);
        vertexShaderEditor->setPlainText(tekst);
    }
}

void MainWindow::saveFragmentShader()
{
    qDebug() << "save fragment";
    const QString filnavn = *fragmentShaderFilnavn;
    QString tekst = fragmentShaderEditor->toPlainText();
    saveFile(filnavn, tekst);
}

void MainWindow::saveVertexShader()
{
    qDebug() << "save vertex";
    const QString filnavn = *vertexShaderFilnavn;
    QString tekst = vertexShaderEditor->toPlainText();
    saveFile(filnavn, tekst);
}
bool MainWindow::loadFile(const QString& filnavn, QString& tekst)
{
    QFile fil(filnavn);
    if (!fil.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("App"), tr("kan ikke lese %1:\n%2").arg(filnavn).arg(fil.errorString()));
        return false;
    }
    QTextStream inn(&fil);
    tekst = inn.readAll();
    return true;
}

bool MainWindow::saveFile(const QString& filnavn, QString& tekst)
{
    QFile fil(filnavn);
    if (!fil.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("ShaderApp"), tr("Kan ikke skrive %1:\n%2.").arg(filnavn).arg(fil.errorString()));
        return false;
    }
    QTextStream ut(&fil);
    ut << tekst;
    return true;
}
void MainWindow::redigert()
{
    //GLWidget* glw = dynamic_cast<GLWidget*>(glWidget);
    //glw->initializeShader();
    QWidget* ut = glWidget;
    glWidget = new GLWidget(this);
    m_hBoxLayout->addWidget(glWidget);
    delete ut;
    kobleSignalsAndSlots();
    buttons[5]->setText("start");
    //repaint();
}

void MainWindow::repaint()
{
    QMainWindow::repaint();

}

