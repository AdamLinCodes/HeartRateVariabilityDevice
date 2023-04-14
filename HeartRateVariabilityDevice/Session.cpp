#include "Session.h"

Session::Session(QWidget* parent) : QObject(parent) {
    logs = new QVector<SessionLog*>();
}

Session::~Session() {
    // destructor
    delete logs;
}

QLineSeries* Session::createNewSession(){
    qsrand(QTime::currentTime().msec());

    int coherenceLevel = qrand() % 3 + 1;
    QLineSeries* series;

    switch(coherenceLevel) {
        case 1:
            series = Graph::newCoherence(1);
            logs->append(new SessionLog(series, 1));
            break;
        case 2:
            series = Graph::newCoherence(2);
            logs->append(new SessionLog(series, 2));
            break;
        default:
            series = Graph::newCoherence(3);
            logs->append(new SessionLog(series, 3));
            break;
    }
    return series;
}

int Session::getNumSessions() {
    return logs->size();
    // return logs->size();
}

QVector<SessionLog*>* Session::getLogs() {
    return logs;
}




