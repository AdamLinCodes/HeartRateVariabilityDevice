#include "Graph.h"

Graph::Graph(QWidget* parent) : QChartView(parent) {
    highCoherenceSeries = new QLineSeries;
    midCoherenceSeries = new QLineSeries;
    lowCoherenceSeries = new QLineSeries;

    // Set the range of the random numbers for each coherence level
  const qreal highRangeMin = 0.5;
  const qreal highRangeMax = 1.0;

  const qreal medhRangeMin = 0.5;
  const qreal medhRangeMax = 53.75;

  const qreal lowRangeMin = 1.5;
  const qreal lowRangeMax = 183.5;

  // Add the randomized values to the high coherence QLineSeries

  int avgMid = 2;
  bool increase = true;
  for (int i = 0; i < 100; i++) {
      qreal randomValue = qrand() / (qreal)RAND_MAX * (highRangeMax - highRangeMin) + highRangeMin;
      if (i % 2 == 0){
          highCoherenceSeries->append(i, avgMid);
      }else if (increase){
          highCoherenceSeries->append(i, avgMid + randomValue);
          increase = !increase;
      }else{
          highCoherenceSeries->append(i, avgMid - randomValue);
          increase = !increase;
      }
  }

  increase = true;
  for (int i = 0; i < 100; i++) {
      qreal randomValue = qrand() / (qreal)RAND_MAX * (medhRangeMax - medhRangeMin) + medhRangeMin;
      if (i % 2 == 0){
          midCoherenceSeries->append(i, avgMid);
      }else if (increase){
          midCoherenceSeries->append(i, avgMid + randomValue);
          increase = !increase;
      }else{
          midCoherenceSeries->append(i, avgMid - randomValue);
          increase = !increase;
      }
  }

  increase = true;
  avgMid = 45;
  for (int i = 0; i < 100; i++) {
      qreal randomValue = qrand() / (qreal)RAND_MAX * (lowRangeMax - lowRangeMin) + lowRangeMin;
      if (i % 2 == 0){
          lowCoherenceSeries->append(i, randomValue);
      }else if (increase){
          lowCoherenceSeries->append(i, avgMid + randomValue);
          increase = !increase;
      }else{
          lowCoherenceSeries->append(i, avgMid - randomValue);
          increase = !increase;
      }
  }
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
