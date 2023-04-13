#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setupChart()
{

    // Heart Rhythm chart stuff
    coherenceGraphView = new Graph();
    QLineSeries* emptySeries = new QLineSeries;


    coherenceGraphView->setRenderHint(QPainter::Antialiasing);
    coherenceGraphView->chart()->addSeries(emptySeries);
    coherenceGraphView->setFixedSize(450, 200);
}

void MainWindow::setupLights() {
    lightsView = new Lights();
}

void MainWindow::setupMenuBox(QGridLayout *buttonsGridLayout)
{
    menuBox = new Menu();
    menuBox->setEnabled(false);
    buttonsGridLayout->addWidget(menuBox, 0, 0);
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

    //Have all button initially disabled (except powerbutton)
    startStopButton->setEnabled(false);
    menuButton->setEnabled(false);
    upButton->setEnabled(false);
    downButton->setEnabled(false);
    leftButton->setEnabled(false);
    rightButton->setEnabled(false);


    // adding objects to the buttonsGridLayout
    buttonsGridLayout->addWidget(powerButton, 4, 1);
    buttonsGridLayout->addWidget(startStopButton, 2, 2);
    buttonsGridLayout->addWidget(menuButton, 4, 3);

    buttonsGridLayout->addWidget(upButton, 1, 2);
    buttonsGridLayout->addWidget(leftButton, 2, 1);
    buttonsGridLayout->addWidget(rightButton, 2, 3);
    buttonsGridLayout->addWidget(downButton, 3, 2);


    // connecting objects to slots
    QObject :: connect(powerButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
        if ((count % 2) == 1){
            this->turnButtonsOn();
        }else{
            this->turnButtonsOff();
        }
    });
    QObject :: connect(menuButton, &Button::clickedWithCount, [](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
    });
    QObject :: connect(startStopButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
        if (count % 2 == 0) {
            this->lightsView->allOff();
            this->coherenceGraphView->setMidCoherence();
        } else {
            coherenceGraphView->setEmpty();
            this->lightsView->inProgressOn();
        }
    });
    QObject :: connect(upButton, &Button::clickedWithCount, [](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
    });
    QObject :: connect(downButton, &Button::clickedWithCount, [](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
    });
    QObject :: connect(leftButton, &Button::clickedWithCount, [](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
    });
    QObject :: connect(rightButton, &Button::clickedWithCount, [](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
    });
}

void MainWindow::turnButtonsOn(){

    startStopButton->setEnabled(true);
    menuButton->setEnabled(true);
    upButton->setEnabled(true);
    downButton->setEnabled(true);
    leftButton->setEnabled(true);
    rightButton->setEnabled(true);

    menuBox->setEnabled(true);
}

void MainWindow::turnButtonsOff(){
    startStopButton->setEnabled(false);
    menuButton->setEnabled(false);
    upButton->setEnabled(false);
    downButton->setEnabled(false);
    leftButton->setEnabled(false);
    rightButton->setEnabled(false);

    menuBox->setEnabled(false);
    coherenceGraphView->setEmpty();
}

Graph* MainWindow::getCoherenceGraphView() {
    return coherenceGraphView;
}

Lights* MainWindow::getLightsView() {
    return lightsView;
}


MainWindow::~MainWindow()
{
    delete ui;
}

