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
#include "Button.h"
#include "Menu.h"
#include "Graph.h"
#include "Lights.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

using namespace QtCharts;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setupChart();
    void setupLights();
    void setupButtons(QGridLayout*);
    void setupMenuBox(QGridLayout*);
    void turnButtonsOn();
    void turnButtonsOff();
    Graph* getCoherenceGraphView();
    Lights* getLightsView();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Button* powerButton;
    Button* startStopButton;
    Button* upButton;
    Button* downButton;
    Button* leftButton;
    Button* rightButton;
    Button* menuButton;

    Graph* coherenceGraphView;
    Lights* lightsView;

    Menu* menuBox;
};
#endif // MAINWINDOW_H
