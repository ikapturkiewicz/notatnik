#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication program(argc, argv);
    MainWindow w;
    w.show();

    return program.exec();
}
