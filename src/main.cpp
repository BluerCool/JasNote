#include <QApplication>
#include <oclero/qlementine.hpp>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("JasNote");
    app.setOrganizationName("JasNote");

    auto *style = new oclero::qlementine::QlementineStyle(&app);
    QApplication::setStyle(style);

    MainWindow window;
    window.show();

    return app.exec();
}
