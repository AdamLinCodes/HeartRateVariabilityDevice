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
    QChartView *chartView = new QChartView;
    QGraphicsView* buttonsView = new QGraphicsView();
    buttonsView->setLayout(buttonsGridLayout);

    // Graphic setups for the heart-rate chart, and the buttons layout
    w.setupChart(chartView);
    w.setupButtons(buttonsGridLayout);

    // Add the chart and buttons the main layout
    widgetLayout->addWidget(chartView, 1, 0);
    widgetLayout->addWidget(buttonsView, 2, 0);
    centralWidget->setLayout(widgetLayout);

    // display the mainwindow
    w.setCentralWidget(centralWidget);
    w.show();
    return a.exec();
}
