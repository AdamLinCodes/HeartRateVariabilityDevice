#include "Session.h"

Session::Session(QWidget* parent) : QObject(parent), currLength(0.0), currAcheivement(0.0), currCoherence(0.0), currLevel("") {
    logs = new QVector<QString>();
}

Session::~Session() {
    // destructor
    delete logs;
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

int Session::createNewSession(){
    qsrand(QTime::currentTime().msec());

    int coherenceLevel = qrand() % 3 + 1;

    switch(coherenceLevel) {
        case 1:
            logs->append("low");
            return 1;
            break;
        case 2:
            logs->append("mid");
            return 2;
            break;
        default:
            logs->append("high");
            return 3;
            break;
    }
}
