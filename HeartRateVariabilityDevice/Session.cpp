#include "Session.h"

Session::Session(QWidget* parent) : currLength(0.0), currAcheivement(0.0), currCoherence(0.0), currLevel("") {
}

Session::~Session() {
    // destructor
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

QString Session::getLevel(){
    return currLevel;
}
