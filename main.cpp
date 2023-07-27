#include "appwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName("Prosoft-Systems");
    QCoreApplication::setApplicationName("Prosoft-Systems_Entrance_Test");

    QApplication a(argc, argv);
    AppWindow w;
    w.show();
    return a.exec();
}
