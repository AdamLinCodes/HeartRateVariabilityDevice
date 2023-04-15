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

void MainWindow::setupBattery() {
    battery = new Battery();
}

void MainWindow::setupMenu(QGridLayout *sessionButtonsGridLayout)
{
    menuView = new QGraphicsView();
    QGridLayout* menuButtonsGridLayout = new QGridLayout();
    menuView->setLayout(menuButtonsGridLayout);

    sessionButton = new Button("Run Session");
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
        this->battery->losePower(1);
        this->getMenuView()->hide();
        this->getCoherenceGraphView()->show();

        startStopButton->setEnabled(true);
        upButton->setEnabled(false);
        downButton->setEnabled(false);
        leftButton->setEnabled(false);
        rightButton->setEnabled(false);


        if (this->battery->isDead()) {
            this->powerOff();
        }
        trackSession.append("Session");
    });
    QObject :: connect(logsButton, &Button::clickedWithCount, [this, sessionButtonsGridLayout](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
        this->battery->losePower(1);
        this->getMenuView()->hide();
        this->getCoherenceGraphView()->show();

        startStopButton->setEnabled(false);
        upButton->setEnabled(false);
        downButton->setEnabled(false);
        leftButton->setEnabled(true);
        rightButton->setEnabled(true);

        if (this->battery->isDead()) {
            this->powerOff();
        }
        trackSession.append("Logs");
    });
    QObject :: connect(settingsButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        qDebug() << name << "Button clicked " << count << " times";
        trackSession.append("Settings");
    });
}

void MainWindow::setupButtons(QGridLayout *buttonsGridLayout)
{
    // button instantiations
    powerButton = new Button("");
    startStopButton = new Button("Start/Stop");
    menuButton = new Button("");
    goBackButton = new Button("");

    upButton = new Button("");
    downButton = new Button("");
    leftButton = new Button("");
    rightButton = new Button("");

    QPixmap pixmap(":/res/powerButton.svg");
    QIcon icon(pixmap);
    powerButton->setIcon(icon);

    QPixmap pixmap2(":/res/menuButton.svg");
    QIcon icon2(pixmap2);
    menuButton->setIcon(icon2);

    QPixmap pixmap3(":/res/upButton.svg");
    QIcon icon3(pixmap3);
    upButton->setIcon(icon3);

    QPixmap pixmap4(":/res/downButton.svg");
    QIcon icon4(pixmap4);
    downButton->setIcon(icon4);

    QPixmap pixmap5(":/res/leftButton.svg");
    QIcon icon5(pixmap5);
    leftButton->setIcon(icon5);

    QPixmap pixmap6(":/res/rightButton.svg");
    QIcon icon6(pixmap6);
    rightButton->setIcon(icon6);

    QPixmap pixmap7(":/res/backButton.svg");
    QIcon icon7(pixmap7);
    goBackButton->setIcon(icon7);

    //Have all button initially disabled (except powerbutton)
    startStopButton->setEnabled(false);
    menuButton->setEnabled(false);
    upButton->setEnabled(false);
    downButton->setEnabled(false);
    leftButton->setEnabled(false);
    rightButton->setEnabled(false);
    goBackButton->setEnabled(false);


    // adding objects to the buttonsGridLayout
    buttonsGridLayout->addWidget(powerButton, 4, 1);
    buttonsGridLayout->addWidget(startStopButton, 2, 3);
    buttonsGridLayout->addWidget(menuButton, 4, 4);
    buttonsGridLayout->addWidget(goBackButton, 1, 1);

    buttonsGridLayout->addWidget(upButton, 1, 3);
    buttonsGridLayout->addWidget(leftButton, 2, 2);
    buttonsGridLayout->addWidget(rightButton, 2, 4);
    buttonsGridLayout->addWidget(downButton, 3, 3);


    // connecting objects to slots
    QObject :: connect(powerButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        qDebug()<< "Power Button Button clicked " << count << " times";
        if ((count % 2) == 1){
            this->powerOn();
        }else{
            this->powerOff();
        }
    });
    QObject :: connect(menuButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        this->battery->losePower(1);
        qDebug() << "Menu Button clicked " << count << " times";
        lightsView->allOff();
        this->getCoherenceGraphView()->hide();
        this->getMenuView()->show();
        if (this->battery->isDead()) {
            this->powerOff();
        }
    });
    QObject :: connect(startStopButton, &Button::clickedWithCount, [this](int count, const QString& name) {

        if (count % 2 == 0) {
            this->battery->losePower(10);
            qDebug() << this->battery->isDead();

            this->lightsView->allOff();
            QLineSeries* series = this->session->createNewSession();
            this->currentSession = this->session->getNumSessions();
            this->coherenceGraphView->setCoherence(series);

            int coherence = this->session->getLogs()->last()->getLevel();
            switch (coherence) {
            case 1:
                this->lightsView->lowCoherenceOn();
                break;
            case 2:
                this->lightsView->midCoherenceOn();
                break;
            default:
                this->lightsView->highCoherenceOn();
                break;
            }

        } else {
            coherenceGraphView->setEmpty();
            this->lightsView->allOff();
            this->lightsView->inProgressOn();
        }

        if (this->battery->isDead()) {
            this->powerOff();
        }
    });
    QObject :: connect(goBackButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        qDebug() << name << "Go Back Button clicked " << count << " times";

        if (trackSession.size() > 0){
            if (trackSession[trackSession.size()-1] == "Session"){
                this->battery->losePower(1);
                this->getMenuView()->hide();
                this->getCoherenceGraphView()->show();

                startStopButton->setEnabled(true);
                upButton->setEnabled(false);
                downButton->setEnabled(false);
                leftButton->setEnabled(false);
                rightButton->setEnabled(false);


                if (this->battery->isDead()) {
                    this->powerOff();
                }
            }else if (trackSession[trackSession.size()-1] == "Logs"){
                this->battery->losePower(1);
                this->getMenuView()->hide();
                this->getCoherenceGraphView()->show();

                startStopButton->setEnabled(false);
                upButton->setEnabled(false);
                downButton->setEnabled(false);
                leftButton->setEnabled(true);
                rightButton->setEnabled(true);

                if (this->battery->isDead()) {
                    this->powerOff();
                }
            }
            trackSession.removeLast();
        }
    });
    QObject :: connect(upButton, &Button::clickedWithCount, [](int count, const QString& name) {
        qDebug() << name << "Up Button clicked " << count << " times";
    });
    QObject :: connect(downButton, &Button::clickedWithCount, [](int count, const QString& name) {
        qDebug() << name << "Down Button clicked " << count << " times";
    });
    QObject :: connect(leftButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        this->battery->losePower(2);
        coherenceGraphView->setEmpty();
        this->lightsView->allOff();

        if(this->currentSession >= this->session->getNumSessions() - 1) {
            this->currentSession--;
        }


        if(this->currentSession >= 0) {
            SessionLog* sessionLog = this->session->getLogs()->at(this->currentSession);

            this->currentSession--;

            this->coherenceGraphView->setCoherence(sessionLog->getSeries());
            int coherence = sessionLog->getLevel();

            if (coherence == 1) {
                this->lightsView->lowCoherenceOn();
            }
            else if (coherence == 2) {
                this->lightsView->midCoherenceOn();
            }
            else {
                this->lightsView->highCoherenceOn();
            }
        }
        else {
            qDebug() << "End of the logs reached";
        }

        if (this->battery->isDead()) {
            this->powerOff();
        }

    });
    QObject :: connect(rightButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        this->battery->losePower(2);
        coherenceGraphView->setEmpty();
        this->lightsView->allOff();


        if(this->currentSession < 0) {
            this->currentSession++;
        }

        if(this->currentSession <= this->session->getNumSessions() - 1) {
            SessionLog* sessionLog = this->session->getLogs()->at(this->currentSession);

            this->currentSession++;

            this->coherenceGraphView->setCoherence(sessionLog->getSeries());
            int coherence = sessionLog->getLevel();

            if (coherence == 1) {
                this->lightsView->lowCoherenceOn();
            }
            else if (coherence == 2) {
                this->lightsView->midCoherenceOn();
            }
            else {
                this->lightsView->highCoherenceOn();
            }
        }
        else {
            qDebug() << "Back at the top of the logs";
        }

        if (this->battery->isDead()) {
            this->powerOff();
        }
    });
}

void MainWindow::powerOn(){
    if (!this->battery->isDead()) {
        sessionButton->setEnabled(true);
        settingsButton->setEnabled(true);
        logsButton->setEnabled(true);
        menuButton->setEnabled(true);
        goBackButton->setEnabled(true);
    } else {
        qDebug() << "Device is dead";
    }
}

void MainWindow::powerOff() {

    sessionButton->setEnabled(false);
    settingsButton->setEnabled(false);
    logsButton->setEnabled(false);

    startStopButton->setEnabled(false);
    menuButton->setEnabled(false);
    upButton->setEnabled(false);
    downButton->setEnabled(false);
    leftButton->setEnabled(false);
    rightButton->setEnabled(false);
    goBackButton->setEnabled(false);

    coherenceGraphView->setEmpty();
    lightsView->allOff();
}

Graph* MainWindow::getCoherenceGraphView() {
    return coherenceGraphView;
}

Lights* MainWindow::getLightsView() {
    return lightsView;
}

Battery* MainWindow::getBattery() {
    return battery;
}

QGraphicsView* MainWindow::getMenuView(){
    return menuView;
}

MainWindow::~MainWindow()
{
    delete ui;
}

