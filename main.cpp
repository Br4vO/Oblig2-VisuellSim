#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "mainwidget.h"
#include "statemanager.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("ORF 2015");
    app.setApplicationVersion("0.1");
#ifndef QT_NO_OPENGL
    MainWidget widget;
    widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
