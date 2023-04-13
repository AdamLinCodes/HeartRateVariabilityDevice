#include "Graph.h"

Graph::Graph(QWidget* parent) : QChartView(parent) {
    highCoherenceSeries = new QLineSeries;
    midCoherenceSeries = new QLineSeries;
    lowCoherenceSeries = new QLineSeries;

    highCoherenceSeries->append(0, 2);
    highCoherenceSeries->append(1, 3);
    highCoherenceSeries->append(2, 2);
    highCoherenceSeries->append(3, 1);
    highCoherenceSeries->append(4, 2);
    highCoherenceSeries->append(5, 3);
    highCoherenceSeries->append(6, 2);
    highCoherenceSeries->append(7, 1);
    highCoherenceSeries->append(8, 2);
    highCoherenceSeries->append(9, 3);
    highCoherenceSeries->append(10, 2);
    highCoherenceSeries->append(11, 1);
    highCoherenceSeries->append(12, 2);
    highCoherenceSeries->append(13, 3);
    highCoherenceSeries->append(14, 2);
    highCoherenceSeries->append(15, 1);
    highCoherenceSeries->append(16, 2);
    highCoherenceSeries->append(17, 3);
    highCoherenceSeries->append(18, 2);
    highCoherenceSeries->append(19, 1);
    highCoherenceSeries->append(20, 2);
    highCoherenceSeries->setPen(QPen(Qt::blue));

    midCoherenceSeries->append(0, 2);
    midCoherenceSeries->append(1, 3);
    midCoherenceSeries->append(2, 4);
    midCoherenceSeries->append(3, 5);
    midCoherenceSeries->append(4, 6);
    midCoherenceSeries->append(5, 7);
    midCoherenceSeries->append(6, 8);
    midCoherenceSeries->setPen(QPen(Qt::green));

    lowCoherenceSeries->append(0, 2);
    lowCoherenceSeries->append(1, 3);
    lowCoherenceSeries->append(2, 4);
    lowCoherenceSeries->append(3, 5);
    lowCoherenceSeries->append(4, 6);
    lowCoherenceSeries->append(5, 7);
    lowCoherenceSeries->append(6, 8);
    lowCoherenceSeries->setPen(QPen(Qt::red));
}

Graph::~Graph() {
    delete lowCoherenceSeries;
    delete midCoherenceSeries;
    delete highCoherenceSeries;
}


void Graph::setHighCoherence() {
    QAbstractSeries* oldSeries = this->chart()->series().at(0);
    this->chart()->removeSeries(oldSeries);

    // chartView->setRenderHint(QPainter::Antialiasing);
    this->chart()->addSeries(highCoherenceSeries);
    this->setFixedSize(450, 200);
}

void Graph::setMidCoherence() {
    QAbstractSeries* oldSeries = this->chart()->series().at(0);
    this->chart()->removeSeries(oldSeries);

    // chartView->setRenderHint(QPainter::Antialiasing);
    this->chart()->addSeries(midCoherenceSeries);
    this->setFixedSize(450, 200);
}

void Graph::setLowCoherence() {
    QAbstractSeries* oldSeries = this->chart()->series().at(0);
    this->chart()->removeSeries(oldSeries);

    // chartView->setRenderHint(QPainter::Antialiasing);
    this->chart()->addSeries(lowCoherenceSeries);
    this->setFixedSize(450, 200);
}

void Graph::setEmpty() {
    QAbstractSeries* oldSeries = this->chart()->series().at(0);
    this->chart()->removeSeries(oldSeries);

    // chartView->setRenderHint(QPainter::Antialiasing);
    this->chart()->addSeries(new QLineSeries());
    this->setFixedSize(450, 200);
}
