#include <QApplication>
#include <QFileInfo>
#include "mainwindow.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    qputenv("QT_WAYLAND_DISABLE_WINDOWDECORATION", "1");
    QApplication app(argc, argv);
    app.setApplicationName("JasNote");
    app.setOrganizationName("JasNote");

    loadConfig();

    QString filePath;
    if (argc > 1) {
        filePath = QFileInfo(argv[1]).absoluteFilePath();
    }

    MainWindow window(filePath);
    window.setWindowOpacity(0);
    window.show();

    return app.exec();
}
