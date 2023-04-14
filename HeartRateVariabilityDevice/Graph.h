#ifndef GRAPH_H
#define GRAPH_H

#include <QtMath>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QPainter>
#include <QTime>

QT_CHARTS_USE_NAMESPACE

class Graph : public QChartView {
    Q_OBJECT

    public:
        Graph(QWidget* parent = nullptr);
        virtual ~Graph();
        void setCoherence(QLineSeries*);
        void setEmpty();
        static QLineSeries* newCoherence(int level);

};


#endif // GRAPH_H
