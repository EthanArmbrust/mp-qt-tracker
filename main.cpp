#include "mainwindow.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/mp/Varia.ico"));
    MainWindow w;
    w.setWindowTitle("Metroid Prime Autotracker");
    w.show();
    return a.exec();
}

