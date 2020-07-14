#include "mainwindow.h"

#include <QApplication>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <QLabel>

#define VERSION_MAJOR 1
#define VERSION_MINOR 0


void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(int argc, char *argv[])
{
    signal(SIGSEGV, handler);
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/mp/Varia.ico"));
    MainWindow w;
    w.setWindowTitle("Metroid Prime Autotracker v" + QString::number(VERSION_MAJOR) + "." + QString::number(VERSION_MINOR));
    w.show();
    return a.exec();
}

