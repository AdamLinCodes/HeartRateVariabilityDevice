#ifndef SESSION_H
#define SESSION_H

#include <QComboBox>
#include <QTime>
#include <QtCharts/QLineSeries>
#include "SessionLog.h"
#include "Graph.h"

QT_CHARTS_USE_NAMESPACE

class Session : public QObject {
    Q_OBJECT

    public:
        Session(QWidget* parent = nullptr);
        virtual ~Session();

        QLineSeries* createNewSession();
        int getNumSessions();
        QVector<SessionLog*>* getLogs();

    private:
        QVector<SessionLog*> *logs;

};

#endif // SESSION_H
