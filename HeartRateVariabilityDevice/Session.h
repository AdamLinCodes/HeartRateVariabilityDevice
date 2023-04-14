#ifndef SESSION_H
#define SESSION_H

#include <QComboBox>
#include <QTime>
#include "SessionLog.h"
#include "Graph.h"

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
        int createNewSession();
        int getNumSessions();
        QVector<QString>* getLogs();

    private:
        QVector<QString> *logs;
        QVector<SessionLog*> *logs2;
        double currLength;
        double currAcheivement;
        double currCoherence;
        QString currLevel;

};

#endif // SESSION_H
