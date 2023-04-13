#include "mainwindow.h"


int main(int argc, char *argv[])
{
    // Boiler-plate objects
    QApplication a(argc, argv);
    MainWindow w;

    // Main widget, and main layout
    QWidget* centralWidget = new QWidget(&w);
    QGridLayout* widgetLayout = new QGridLayout();

    // Container objects: views and layouts
    QGridLayout* buttonsGridLayout = new QGridLayout();
    QGraphicsView* buttonsView = new QGraphicsView();
    buttonsView->setLayout(buttonsGridLayout);
    QGraphicsView* logsView = new QGraphicsView();

    logsView->hide();
    // Graphic setups for the heart-rate chart, and the buttons layout
    w.setupSession();
    w.setupLights();
    w.setupChart();
    w.setupButtons(buttonsGridLayout);
    w.setupMenuBox(buttonsGridLayout);

    // Add the chart and buttons the main layout
    widgetLayout->addWidget(w.getLightsView(), 0, 0);
    widgetLayout->addWidget(w.getCoherenceGraphView(), 1, 0);
    widgetLayout->addWidget(logsView, 2, 0);
    widgetLayout->addWidget(buttonsView, 3, 0);

    centralWidget->setLayout(widgetLayout);

    // display the mainwindow
    w.setCentralWidget(centralWidget);
    w.show();
    return a.exec();
}
