#ifndef GRAPH_H
#define GRAPH_H

#include <QtMath>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QPainter>

QT_CHARTS_USE_NAMESPACE

class Graph : public QChartView {
    Q_OBJECT

    public:
        Graph(QWidget* parent = nullptr);
        virtual ~Graph();

        void setHighCoherence();
        void setMidCoherence();
        void setLowCoherence();
        void setEmpty();

    private:
        QLineSeries* lowCoherenceSeries;
        QLineSeries* midCoherenceSeries;
        QLineSeries* highCoherenceSeries;

};


#endif // GRAPH_H
