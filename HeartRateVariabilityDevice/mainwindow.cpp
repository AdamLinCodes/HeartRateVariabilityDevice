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

void MainWindow::setupSettings(QGridLayout *sessionButtonsGridLayout)
{
    settingsView = new QGraphicsView();
    QGridLayout* settingsButtonsGridLayout = new QGridLayout();
    settingsView->setLayout(settingsButtonsGridLayout);

    lowPowerModeRadioButton = new QRadioButton("Low Power Mode");

    settingsView->hide();

    settingsButtonsGridLayout->addWidget(lowPowerModeRadioButton, 2, 2);

    connect(lowPowerModeRadioButton, &QRadioButton::toggled, this, &MainWindow::updatePowerMode);

}

void MainWindow::setupMenu(QGridLayout *sessionButtonsGridLayout)
{
    menuView = new QGraphicsView();
    QGridLayout* menuButtonsGridLayout = new QGridLayout();
    menuView->setLayout(menuButtonsGridLayout);

    upButton = new Button("");
    downButton = new Button("");
    okButton = new Button("");


    QPixmap pixmap3(":/res/upButton.svg");
    QIcon icon3(pixmap3);
    upButton->setIcon(icon3);

    QPixmap pixmap4(":/res/downButton.svg");
    QIcon icon4(pixmap4);
    downButton->setIcon(icon4);

    QPixmap pixmap5(":/res/okButton.svg");
    QIcon icon5(pixmap5);
    okButton->setIcon(icon5);


    sessionButtonsGridLayout->addWidget(downButton, 3, 3);
    sessionButtonsGridLayout->addWidget(upButton, 1, 3);
    sessionButtonsGridLayout->addWidget(okButton, 2, 3);


    sessionRadioButton = new QRadioButton("Run Session");
    logsRadioButton = new QRadioButton("Logs/History");
    settingsRadioButton = new QRadioButton("Settings");

    sessionRadioButton->setChecked(true);

    menuButtonsGridLayout->addWidget(sessionRadioButton, 2, 2);
    menuButtonsGridLayout->addWidget(logsRadioButton, 3, 2);
    menuButtonsGridLayout->addWidget(settingsRadioButton, 4, 2);

    menuButtonsGridLayout->setColumnStretch(0,1);
    menuButtonsGridLayout->setColumnStretch(1,1);
    menuButtonsGridLayout->setColumnStretch(2,2);
    menuButtonsGridLayout->setColumnStretch(3,1);
    menuButtonsGridLayout->setColumnStretch(4,1);

    QObject :: connect(upButton, &Button::clickedWithCount, [this, sessionButtonsGridLayout](int count, const QString& name) {
        qDebug() << "Up Button clicked " << count << " times";
        if (settingsRadioButton->isChecked()){
            logsRadioButton->setChecked(true);
        }else if (logsRadioButton->isChecked()){
            sessionRadioButton->setChecked(true);
        }else{
            settingsRadioButton->setChecked(true);
        }
    });
    QObject :: connect(downButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        qDebug() << "Down Button clicked " << count << " times";
        if (sessionRadioButton->isChecked()){
            logsRadioButton->setChecked(true);
        }else if (logsRadioButton->isChecked()){
            settingsRadioButton->setChecked(true);
        }else{
            sessionRadioButton->setChecked(true);
        }
    });

    upButton->setEnabled(false);
    downButton->setEnabled(false);
    okButton->setEnabled(false);

    QObject :: connect(okButton, &Button::clickedWithCount, [this, sessionButtonsGridLayout](int count, const QString& name) {
        if (sessionRadioButton->isChecked()){
            if (!lowPowerModeOn){
                this->battery->losePower(1);
            }
            this->getMenuView()->hide();
            this->getCoherenceGraphView()->show();

            startStopButton->setEnabled(true);
            upButton->setEnabled(false);
            downButton->setEnabled(false);
            leftButton->setEnabled(false);
            rightButton->setEnabled(false);

            okButton->hide();
            startStopButton->show();


            if (this->battery->isDead()) {
                this->powerOff();
            }
            trackSession.append("Session");
        }else if(logsRadioButton->isChecked()){
            if (!lowPowerModeOn){
                this->battery->losePower(1);
            }
            this->getMenuView()->hide();
            this->getCoherenceGraphView()->show();

            startStopButton->setEnabled(false);
            okButton->setEnabled(false);
            upButton->setEnabled(false);
            downButton->setEnabled(false);
            leftButton->setEnabled(true);
            rightButton->setEnabled(true);

            if (this->battery->isDead()) {
                this->powerOff();
            }
            trackSession.append("Logs");
        }else if(settingsRadioButton->isChecked()){
            if (!lowPowerModeOn){
                this->battery->losePower(1);
            }
            this->getMenuView()->hide();
            this->getCoherenceGraphView()->hide();
            this->getSettingsView()->show();
            leftButton->setEnabled(false);
            rightButton->setEnabled(false);
            upButton->setEnabled(false);
            downButton->setEnabled(false);
            startStopButton->setEnabled(false);
            okButton->setEnabled(false);
            trackSession.append("Settings");
        }


    });
}

void MainWindow::setupButtons(QGridLayout *buttonsGridLayout)
{
    // button instantiations
    powerButton = new Button("");
    startStopButton = new Button("Start/Stop");
    menuButton = new Button("");
    goBackButton = new Button("");

    leftButton = new Button("");
    rightButton = new Button("");

    QPixmap pixmap(":/res/powerButton.svg");
    QIcon icon(pixmap);
    powerButton->setIcon(icon);

    QPixmap pixmap2(":/res/menuButton.svg");
    QIcon icon2(pixmap2);
    menuButton->setIcon(icon2);

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
    leftButton->setEnabled(false);
    rightButton->setEnabled(false);
    goBackButton->setEnabled(false);


    // adding objects to the buttonsGridLayout
    buttonsGridLayout->addWidget(powerButton, 4, 1);
    buttonsGridLayout->addWidget(startStopButton, 2, 3);
    buttonsGridLayout->addWidget(menuButton, 4, 4);
    buttonsGridLayout->addWidget(goBackButton, 1, 1);

    buttonsGridLayout->addWidget(leftButton, 2, 2);
    buttonsGridLayout->addWidget(rightButton, 2, 4);

    startStopButton->hide();


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
        if (!lowPowerModeOn){
            this->battery->losePower(1);
        }
        qDebug() << "Menu Button clicked " << count << " times";
        lightsView->allOff();
        this->getCoherenceGraphView()->hide();
        this->getSettingsView()->hide();
        this->getMenuView()->show();
        if (this->battery->isDead()) {
            this->powerOff();
        }
        startStopButton->setEnabled(false);
        leftButton->setEnabled(false);
        rightButton->setEnabled(false);

        upButton->setEnabled(true);
        okButton->setEnabled(true);
        downButton->setEnabled(true);
        startStopButton->hide();
        okButton->show();
        qDebug() << lowPowerModeOn;
    });
    QObject :: connect(startStopButton, &Button::clickedWithCount, [this](int count, const QString& name) {

        if (count % 2 == 0) {
            if (!lowPowerModeOn){
                this->battery->losePower(10);
            }else{
                this->battery->losePower(5);
            }
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
                if (!lowPowerModeOn){
                    this->battery->losePower(1);
                }
                this->getMenuView()->hide();
                this->getSettingsView()->hide();
                this->getCoherenceGraphView()->show();
                okButton->hide();
                startStopButton->show();

                startStopButton->setEnabled(true);
                leftButton->setEnabled(false);
                rightButton->setEnabled(false);


                if (this->battery->isDead()) {
                    this->powerOff();
                }
            }else if (trackSession[trackSession.size()-1] == "Logs"){
                if (!lowPowerModeOn){
                    this->battery->losePower(1);
                }
                this->getMenuView()->hide();
                this->getSettingsView()->hide();
                this->getCoherenceGraphView()->show();

                startStopButton->setEnabled(false);
                leftButton->setEnabled(true);
                rightButton->setEnabled(true);

                if (this->battery->isDead()) {
                    this->powerOff();
                }
            }else if (trackSession[trackSession.size()-1] == "Settings"){
                if (!lowPowerModeOn){
                    this->battery->losePower(1);
                }
                this->getMenuView()->hide();
                this->getCoherenceGraphView()->hide();
                this->getSettingsView()->show();
                leftButton->setEnabled(false);
                rightButton->setEnabled(false);
                upButton->setEnabled(false);
                downButton->setEnabled(false);
                startStopButton->setEnabled(false);
                okButton->setEnabled(false);
            }
            trackSession.removeLast();
        }
    });
    QObject :: connect(leftButton, &Button::clickedWithCount, [this](int count, const QString& name) {
        if (!lowPowerModeOn){
            this->battery->losePower(2);
        }else{
            this->battery->losePower(1);
        }
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
        if (!lowPowerModeOn){
            this->battery->losePower(2);
        }else{
            this->battery->losePower(1);
        }
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
        menuButton->setEnabled(true);
        goBackButton->setEnabled(true);
        upButton->setEnabled(true);
        downButton->setEnabled(true);
        okButton->setEnabled(true);
    } else {
        qDebug() << "Device is dead";
    }
}

void MainWindow::powerOff() {
    startStopButton->setEnabled(false);
    menuButton->setEnabled(false);
    upButton->setEnabled(false);
    downButton->setEnabled(false);
    okButton->setEnabled(false);
    leftButton->setEnabled(false);
    rightButton->setEnabled(false);
    goBackButton->setEnabled(false);

    coherenceGraphView->setEmpty();
    lightsView->allOff();
}

void MainWindow::updatePowerMode(bool enabled){
    lowPowerModeOn = enabled;
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

QGraphicsView* MainWindow::getSettingsView(){
    return settingsView;
}

QGraphicsView* MainWindow::getMenuView(){
    return menuView;
}

MainWindow::~MainWindow()
{
    delete ui;
}

