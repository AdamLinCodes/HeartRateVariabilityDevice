#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QPainter>
#include <QComboBox>
#include <QRadioButton>
#include "Button.h"
#include "Graph.h"
#include "Lights.h"
#include "Session.h"
#include "Battery.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

using namespace QtCharts;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setupSession();
    void setupChart();
    void setupLights();
    void setupBattery();
    void setupButtons(QGridLayout*);
    void setupMenu(QGridLayout*);
    void setupSettings(QGridLayout*);
    void powerOn();
    void powerOff();
    void updatePowerMode(bool);
    Graph* getCoherenceGraphView();
    Lights* getLightsView();
    QGraphicsView* getMenuView();
    QGraphicsView* getSettingsView();
    Battery* getBattery();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Button* sessionButton;
    Button* settingsButton;
    Button* logsButton;

    QRadioButton* sessionRadioButton;
    QRadioButton* settingsRadioButton;
    QRadioButton* logsRadioButton;

    QRadioButton* lowPowerModeRadioButton;

    Button* powerButton;
    Button* startStopButton;
    Button* upButton;
    Button* downButton;
    Button* okButton;
    Button* leftButton;
    Button* rightButton;
    Button* menuButton;
    Button* goBackButton;

    Graph* coherenceGraphView;
    Lights* lightsView;
    Session* session;
    Battery* battery;
    QGraphicsView* menuView;
    QGraphicsView* settingsView;
    int currentSession;
    QStringList trackSession;
    bool lowPowerModeOn = false;
};
#endif // MAINWINDOW_H
