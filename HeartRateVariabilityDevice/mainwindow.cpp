#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setupChart(QChartView* chartView)
{

    // Heart Rhythm chart stuff
    QLineSeries* heartSeries = new QLineSeries;
    heartSeries->append(0, 1);
    heartSeries->append(1, 2);
    heartSeries->append(2, 3);
    heartSeries->append(3, 4);
    heartSeries->append(4, 8);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->addSeries(heartSeries);
    chartView->setFixedSize(450, 200);
}
void MainWindow::setupButtons(QGridLayout *buttonsGridLayout)
{
    // button instantiations
    powerButton = new Button("On/Off");
    startStopButton = new Button("Start/Stop");
    menuButton = new Button("Menu");

    upButton = new Button("UP");
    downButton = new Button("Down");
    leftButton = new Button("LEFT");
    rightButton = new Button("RIGHT");


    // adding objects to the buttonsGridLayout
    buttonsGridLayout->addWidget(powerButton, 4, 1);
    buttonsGridLayout->addWidget(startStopButton, 2, 2);
    buttonsGridLayout->addWidget(menuButton, 4, 3);

    buttonsGridLayout->addWidget(upButton, 1, 2);
    buttonsGridLayout->addWidget(leftButton, 2, 1);
    buttonsGridLayout->addWidget(rightButton, 2, 3);
    buttonsGridLayout->addWidget(downButton, 3, 2);


    // connecting objects to slots
    QObject :: connect(powerButton, &Button::clickedWithCount, [](int count) {
        qDebug() << "Power Button clicked " << count << " times";
    });
    QObject :: connect(menuButton, &Button::clickedWithCount, [](int count) {
        qDebug() << "Menu Button clicked " << count << " times";
    });
    QObject :: connect(startStopButton, &Button::clickedWithCount, [](int count) {
        qDebug() << "Start Button clicked " << count << " times";
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

