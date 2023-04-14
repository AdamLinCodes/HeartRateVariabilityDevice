#include "Session.h"

Session::Session(QWidget* parent) : QObject(parent), currLength(0.0), currAcheivement(0.0), currCoherence(0.0), currLevel("") {
    logs = new QVector<QString>();
    logs2 = new QVector<SessionLog*>();
}

Session::~Session() {
    // destructor
    delete logs;
    delete logs2;
}

void Session::setLength(double len){
    currLength = len;
}

void Session::setAcheivement(double ach){
    currAcheivement = ach;
}

void Session::setCoherence(double coh){
    currCoherence = coh;
}

void Session::setLevel(QString& lev){
    currLevel = lev;
}

double Session::getLength(){
    return currLength;
}

double Session::getAcheivement(){
    return currAcheivement;
}

double Session::getCoherence(){
    return currCoherence;
}

QLineSeries* Session::createNewSession(){
    qsrand(QTime::currentTime().msec());

    int coherenceLevel = qrand() % 3 + 1;
    QLineSeries* series;

    switch(coherenceLevel) {
        case 1:
            logs->append("low");
            series = Graph::newCoherence(1);
            logs2->append(new SessionLog(series, 1));
            break;
        case 2:
            logs->append("mid");
            series = Graph::newCoherence(2);
            logs2->append(new SessionLog(series, 2));
            break;
        default:
            logs->append("high");
            series = Graph::newCoherence(3);
            logs2->append(new SessionLog(series, 3));
            break;
    }
    return series;
}

int Session::getNumSessions() {
    return logs2->size();
    // return logs->size();
}

QVector<SessionLog*>* Session::getLogs() {
    return logs2;
}




