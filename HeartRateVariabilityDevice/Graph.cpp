#include "Graph.h"

Graph::Graph(QWidget* parent) : QChartView(parent) {

}

Graph::~Graph() {

}


void Graph::setCoherence(QLineSeries* series) {
    QAbstractSeries* oldSeries = this->chart()->series().at(0);
    this->chart()->removeSeries(oldSeries);

    // chartView->setRenderHint(QPainter::Antialiasing);
    this->chart()->addSeries(series);
    this->setFixedSize(450, 200);
}


void Graph::setEmpty() {
    QAbstractSeries* oldSeries = this->chart()->series().at(0);
    this->chart()->removeSeries(oldSeries);

    // chartView->setRenderHint(QPainter::Antialiasing);
    this->chart()->addSeries(new QLineSeries());
    this->setFixedSize(450, 200);
}

QLineSeries* Graph::newCoherence(int level) {
    qreal rangeMin, rangeMax;

    if (level == 1) {
        rangeMin = 1.5;
        rangeMax = 183.5;
    }
    else if (level == 2) {
        rangeMin = 0.5;
        rangeMax = 53.75;
    }
    else {
        rangeMin = 0.5;
        rangeMax = 1.0;
    }
    int avgMid = 2;
    bool increase = true;

    QLineSeries* coherenceSeries = new QLineSeries;
    qsrand(QTime::currentTime().msec());
    for (int i = 0; i < 100; i++) {
        qreal randomValue = qrand() / (qreal)RAND_MAX * (rangeMax - rangeMin) + rangeMin;
        if (i % 2 == 0){
            coherenceSeries->append(i, avgMid);
        }else if (increase){
            coherenceSeries->append(i, avgMid + randomValue);
            increase = !increase;
        }else{
            coherenceSeries->append(i, avgMid - randomValue);
            increase = !increase;
        }
    }

    return coherenceSeries;
}
