#include "mainwindow.h"
#include "input_device.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Input_Dialog dia;
    dia.show();
    w.show();
    return a.exec();
}
