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

        void setLength(double len);
        void setAcheivement(double ach);
        void setCoherence(double coh);
        void setLevel(QString& lev);


        double getLength();
        double getAcheivement();
        double getCoherence();
        QLineSeries* createNewSession();
        int getNumSessions();
        QVector<SessionLog*>* getLogs();

    private:
        QVector<QString> *logs;
        QVector<SessionLog*> *logs2;
        double currLength;
        double currAcheivement;
        double currCoherence;
        QString currLevel;

};

#endif // SESSION_H
