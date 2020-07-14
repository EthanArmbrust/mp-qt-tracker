#include "mainwindow.h"

#include <QApplication>
#include <QLabel>

#define VERSION_MAJOR 1
#define VERSION_MINOR 0


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/mp/Varia.ico"));
    MainWindow w;
    w.setWindowTitle("Metroid Prime Autotracker v" + QString::number(VERSION_MAJOR) + "." + QString::number(VERSION_MINOR));
    w.show();
    return a.exec();
}

