#ifndef SESSIONLOG_H
#define SESSIONLOG_H

#include <QObject>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

class SessionLog : public QObject {
    Q_OBJECT

    public:
        SessionLog(QLineSeries* series, int level, QObject* parent = nullptr);
        int getLevel();
        QLineSeries* getSeries();
        virtual ~SessionLog();

    private:
        QLineSeries* series;
        int level;
};

#endif // SESSIONLOG_H
