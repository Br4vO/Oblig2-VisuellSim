#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class QHBoxLayout;
QT_END_NAMESPACE
class QOpenGLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    QString hentFragmentShaderFilnavn() const;
    QString hentVertexShaderFilnavn() const;
    QString hentFragmentShaderKode() const;
    QString hentVertexShaderKode() const;

public slots:
    void openFragmentShader();
    void openVertexShader();
    void saveFragmentShader();
    void saveVertexShader();
    void redigert();
    void repaint();
signals:
    //void redigert();
    //void musFlyttet();

protected:
    //void mouseMoveEvent(QMouseEvent* event);
    //void paintEvent(QPaintEvent* event);

private:
    void createMenu();
    QLayout* buttonLayout();
    void kobleSignalsAndSlots();

    QHBoxLayout* m_hBoxLayout;
    bool loadFile(const QString& filnavn, QString& tekst);
    bool saveFile(const QString& filnavn, QString& tekst);

    enum { NumGridRows = 3, NumButtons = 13 };

    QMenuBar *menuBar;

    QTextEdit *fragmentShaderEditor;
    QTextEdit *vertexShaderEditor;

    QGroupBox *verticalGroupBox;
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    QMenu *fileMenu;
    QAction* openFragmentAction;
    QAction* openVertexAction;
    QAction* saveFragmentAction;
    QAction* saveVertexAction;
    QAction *exitAction;

    QString* fragmentShaderFilnavn;
    QString* vertexShaderFilnavn;

    QOpenGLWidget* glWidget;
};

#endif
