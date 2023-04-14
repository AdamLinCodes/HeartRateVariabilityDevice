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

    // Graphic setups for the heart-rate chart, and the buttons layout
    w.setupSession();
    w.setupLights();
    w.setupChart();
    w.setupMenu(buttonsGridLayout);
    w.setupButtons(buttonsGridLayout);
    w.setupBattery();

    // Add the chart and buttons the main layout
    widgetLayout->addWidget(w.getLightsView(), 0, 0);
    widgetLayout->addWidget(w.getCoherenceGraphView(), 1, 0);
    widgetLayout->addWidget(w.getMenuView(), 2, 0);
    widgetLayout->addWidget(buttonsView, 3, 0);
    widgetLayout->addWidget(w.getBattery());

    centralWidget->setLayout(widgetLayout);

    // display the mainwindow
    w.setCentralWidget(centralWidget);
    w.show();
    return a.exec();
}
