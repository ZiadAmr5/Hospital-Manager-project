#include <QApplication>
#include "hospmanager.hpp"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    hospman *Hospital = new hospman;

    Hospital->loadinitialData();
     MainWindow w(Hospital);

    w.show();
    return a.exec();
}
