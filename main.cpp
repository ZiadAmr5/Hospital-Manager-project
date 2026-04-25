#include "mainwindow.h"
#include "hospmanager.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    hospman Hospital;
    Hospital.loadinitialData();
    w.show();
    return a.exec();
}
