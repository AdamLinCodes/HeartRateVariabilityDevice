#include "mainwindow.h"

#include <QApplication>

#include "Tester.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Tester* t = new Tester();
    t->print();
    return a.exec();
}
