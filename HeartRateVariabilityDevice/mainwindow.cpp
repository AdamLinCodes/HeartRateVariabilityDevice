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
    coherenceGraphView->chart()->legend()->hide();
    coherenceGraphView->setFixedSize(450, 200);

    coherenceGraphView->hide();
}

void MainWindow::setupSession() {
    currentSession = -1;
    session = new Session();
}

void MainWindow::setupLights() {
    lightsView = new Lights();
}

void MainWindow::setupMenu(QGridLayout *sessionButtonsGridLayout)
{
    menuView = new QGraphicsView();
    QGridLayout* menuButtonsGridLayout = new QGridLayout();
    menuView->setLayout(menuButtonsGridLayout);

    sessionButton = new Button("Start Session");
    settingsButton = new Button("Settings");
    logsButton = new Button("Logs/History");

    menuButtonsGridLayout->addWidget(sessionButton, 2, 2);
    menuButtonsGridLayout->addWidget(logsButton, 4, 3);
    menuButtonsGridLayout->addWidget(settingsButton, 4, 1);


    sessionButton->setEnabled(false);
    logsButton->setEnabled(false);
    settingsButton->setEnabled(false);

    QObject :: connect(sessionButton, &Button::clickedWithCount, [this, sessionButtonsGridLayout](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
        this->getMenuView()->hide();
        this->getCoherenceGraphView()->show();

        qobject_cast<QPushButton*>(sessionButtonsGridLayout->itemAtPosition(2, 2)->widget())->setEnabled(true);
        qobject_cast<QPushButton*>(sessionButtonsGridLayout->itemAtPosition(1, 2)->widget())->setEnabled(false);
        qobject_cast<QPushButton*>(sessionButtonsGridLayout->itemAtPosition(2, 1)->widget())->setEnabled(false);
        qobject_cast<QPushButton*>(sessionButtonsGridLayout->itemAtPosition(2, 3)->widget())->setEnabled(false);
        qobject_cast<QPushButton*>(sessionButtonsGridLayout->itemAtPosition(3, 2)->widget())->setEnabled(false);
    });
    QObject :: connect(logsButton, &Button::clickedWithCount, [this, sessionButtonsGridLayout](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
        this->getMenuView()->hide();
        this->getCoherenceGraphView()->show();
        qobject_cast<QPushButton*>(sessionButtonsGridLayout->itemAtPosition(2, 2)->widget())->setEnabled(false);
        qobject_cast<QPushButton*>(sessionButtonsGridLayout->itemAtPosition(1, 2)->widget())->setEnabled(false);
        qobject_cast<QPushButton*>(sessionButtonsGridLayout->itemAtPosition(2, 1)->widget())->setEnabled(true);
        qobject_cast<QPushButton*>(sessionButtonsGridLayout->itemAtPosition(2, 3)->widget())->setEnabled(true);
        qobject_cast<QPushButton*>(sessionButtonsGridLayout->itemAtPosition(3, 2)->widget())->setEnabled(false);
    });
    QObject :: connect(settingsButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
    });
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
    QObject :: connect(menuButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
        lightsView->allOff();
        this->getCoherenceGraphView()->hide();
        this->getMenuView()->show();
    });
    QObject :: connect(startStopButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
        if (count % 2 == 0) {
            this->lightsView->allOff();
            int coherence = this->session->createNewSession();
            this->currentSession = this->session->getNumSessions();

            switch (coherence) {
            case 1:
                this->lightsView->lowCoherenceOn();
                this->coherenceGraphView->setLowCoherence();
                break;
            case 2:
                this->lightsView->midCoherenceOn();
                this->coherenceGraphView->setMidCoherence();
                break;
            default:
                this->lightsView->highCoherenceOn();
                this->coherenceGraphView->setHighCoherence();
                break;
            }

        } else {
            coherenceGraphView->setEmpty();
            this->lightsView->allOff();
            this->lightsView->inProgressOn();
        }
    });
    QObject :: connect(upButton, &Button::clickedWithCount, [](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
    });
    QObject :: connect(downButton, &Button::clickedWithCount, [](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
    });
    QObject :: connect(leftButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        coherenceGraphView->setEmpty();
        this->lightsView->allOff();

        if(this->currentSession >= this->session->getNumSessions() - 1) {
            this->currentSession--;
        }


        if(this->currentSession >= 0) {
            QString coherence = this->session->getLogs()->at(this->currentSession);
            this->currentSession--;

            if (coherence == "low") {
                this->lightsView->lowCoherenceOn();
                this->coherenceGraphView->setLowCoherence();
            }
            else if (coherence == "mid") {
                this->lightsView->midCoherenceOn();
                this->coherenceGraphView->setMidCoherence();
            }
            else {
                this->lightsView->highCoherenceOn();
                this->coherenceGraphView->setHighCoherence();
            }
        }
        else {
            qDebug() << "End of the logs reached";
        }
    });
    QObject :: connect(rightButton, &Button::clickedWithCount, [this](int count, const QString& name) {

        coherenceGraphView->setEmpty();
        this->lightsView->allOff();


        if(this->currentSession < 0) {
            this->currentSession++;
        }

        if(this->currentSession <= this->session->getNumSessions() - 1) {
            QString coherence = this->session->getLogs()->at(this->currentSession);
            this->currentSession++;

            if (coherence == "low") {
                this->lightsView->lowCoherenceOn();
                this->coherenceGraphView->setLowCoherence();
            }
            else if (coherence == "mid") {
                this->lightsView->midCoherenceOn();
                this->coherenceGraphView->setMidCoherence();
            }
            else {
                this->lightsView->highCoherenceOn();
                this->coherenceGraphView->setHighCoherence();
            }
        }
        else {
            qDebug() << "Back at the top of the logs";
        }
    });
}

void MainWindow::turnButtonsOn(){

    sessionButton->setEnabled(true);
    settingsButton->setEnabled(true);
    logsButton->setEnabled(true);
    menuButton->setEnabled(true);
}

void MainWindow::turnButtonsOff() {

    sessionButton->setEnabled(false);
    settingsButton->setEnabled(false);
    logsButton->setEnabled(false);

    startStopButton->setEnabled(false);
    menuButton->setEnabled(false);
    upButton->setEnabled(false);
    downButton->setEnabled(false);
    leftButton->setEnabled(false);
    rightButton->setEnabled(false);

    coherenceGraphView->setEmpty();
    lightsView->allOff();
}

Graph* MainWindow::getCoherenceGraphView() {
    return coherenceGraphView;
}

Lights* MainWindow::getLightsView() {
    return lightsView;
}

QGraphicsView* MainWindow::getMenuView(){
    return menuView;
}

MainWindow::~MainWindow()
{
    delete ui;
}

