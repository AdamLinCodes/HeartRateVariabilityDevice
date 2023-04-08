#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QGridLayout>

#include "Button.h"


int main(int argc, char *argv[])
{
    // Boiler-plate objects
    QApplication a(argc, argv);
    MainWindow w;


    // Important layout setup
    QWidget* centralWidget = new QWidget(&w);
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setSpacing(20);


    // QObject instantiations
    Button* powerButton = new Button("On/Off");
    Button* upButton = new Button("UP");
    Button* downButton = new Button("Down");
    Button* leftButton = new Button("LEFT");
    Button* rightButton = new Button("RIGHT");


    // adding buttons to the grid
    gridLayout->addWidget(upButton, 0, 1);
    gridLayout->addWidget(leftButton, 1, 0);
    gridLayout->addWidget(rightButton, 1, 2);
    gridLayout->addWidget(downButton, 2, 1);
    gridLayout->addWidget(powerButton, 3, 1);


    // setting up dimensions of the grid
    QHBoxLayout* horizontalLayout = new QHBoxLayout();
    horizontalLayout->addStretch();
    horizontalLayout->addLayout(gridLayout);
    horizontalLayout->addStretch();

    QVBoxLayout* verticalLayout = new QVBoxLayout(centralWidget);
    verticalLayout->addStretch();
    verticalLayout->addLayout(horizontalLayout);
    verticalLayout->addStretch();



    // connecting objects to slots
    QObject :: connect(powerButton, &Button::clickedWithCount, [](int count) {
        qDebug() << "Power Button clicked " << count << " times";
    });
    QObject :: connect(upButton, &Button::clickedWithCount, [](int count) {
        qDebug() << "Up Button clicked " << count << " times";
    });
    QObject :: connect(downButton, &Button::clickedWithCount, [](int count) {
        qDebug() << "Down Button clicked " << count << " times";
    });
    QObject :: connect(leftButton, &Button::clickedWithCount, [](int count) {
        qDebug() << "Left Button clicked " << count << " times";
    });
    QObject :: connect(rightButton, &Button::clickedWithCount, [](int count) {
        qDebug() << "Right Button clicked " << count << " times";
    });



    // display the mainwindow
    w.setCentralWidget(centralWidget);
    w.show();
    return a.exec();
}
