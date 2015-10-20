
#include "MainWindow.h"
#include "glwidget.h"
#include <QApplication>
#include <QTextCodec>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QTextCodec::codecForLocale();

    MainWindow mainWindow;
    mainWindow.resize(1200, 720);
    mainWindow.show();
/*
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3,2);
    format.setProfile(QSurfaceFormat::CoreProfile);
*/
    return app.exec();
}
