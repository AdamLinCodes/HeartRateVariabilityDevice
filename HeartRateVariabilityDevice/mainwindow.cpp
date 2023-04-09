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
    heartSeries->append(4, 5);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->addSeries(heartSeries);
    chartView->setFixedSize(400, 200);
}
void MainWindow::setupButtons(QGridLayout *buttonsGridLayout)
{
    // button instantiations
    Button* powerButton = new Button("On/Off");
    Button* startButton = new Button("Start");
    Button* upButton = new Button("UP");
    Button* downButton = new Button("Down");
    Button* leftButton = new Button("LEFT");
    Button* rightButton = new Button("RIGHT");


    // adding objects to the buttonsGridLayout
    buttonsGridLayout->addWidget(upButton, 1, 2);
    buttonsGridLayout->addWidget(leftButton, 2, 1);
    buttonsGridLayout->addWidget(rightButton, 2, 3);
    buttonsGridLayout->addWidget(downButton, 3, 2);
    buttonsGridLayout->addWidget(powerButton, 4, 2);
    buttonsGridLayout->addWidget(startButton, 2, 2);


    // connecting objects to slots
    QObject :: connect(powerButton, &Button::clickedWithCount, [](int count) {
        qDebug() << "Power Button clicked " << count << " times";
    });
    QObject :: connect(startButton, &Button::clickedWithCount, [](int count) {
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

