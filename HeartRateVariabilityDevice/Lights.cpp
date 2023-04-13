//Lights(QWidget* parent = nullptr);
//virtual ~Lights();

//void inProgressOn();
//void lowCoherenceOn();
//void midCoherenceOn();
//void highCoherenceOn();
//void allOff();

//private:
//QLabel* inProgressLED;
//QLabel* lowCoherenceLED;
//QLabel* midCoherenceLED;
//QLabel* highCoherenceLED;

#include "Lights.h"

Lights::Lights(QWidget* parent) : QGraphicsView(parent) {
    LEDLayout = new QGridLayout();
    this->setLayout(LEDLayout);

    setupLEDs();
}


Lights::~Lights() {
    // destructor
}

void Lights::setupLEDs() {
    // DO THIS PART WHEN YOU GET BACK!!!
    inProgressLED = new QLabel("In Progress");
    lowCoherenceLED = new QLabel("Low");
    midCoherenceLED = new QLabel("Medium");
    highCoherenceLED = new QLabel("High");

    inProgressLED->setAlignment(Qt::AlignCenter);
    lowCoherenceLED->setAlignment(Qt::AlignCenter);
    midCoherenceLED->setAlignment(Qt::AlignCenter);
    highCoherenceLED->setAlignment(Qt::AlignCenter);

    allOff();

    inProgressLED->setFixedSize(70, 40);
    lowCoherenceLED->setFixedSize(70, 40);
    midCoherenceLED->setFixedSize(70, 40);
    highCoherenceLED->setFixedSize(70, 40);

    LEDLayout->addWidget(inProgressLED, 0, 0);
    LEDLayout->addWidget(lowCoherenceLED, 0, 1);
    LEDLayout->addWidget(midCoherenceLED, 0, 2);
    LEDLayout->addWidget(highCoherenceLED, 0, 3);

}



void Lights::inProgressOn() {
    inProgressLED->setStyleSheet("QLabel { border-radius: 10px; background-color: red; }");
}

void Lights::lowCoherenceOn(){
    lowCoherenceLED->setStyleSheet("QLabel { border-radius: 10px; background-color: yellow; }");
}

void Lights::midCoherenceOn(){
    midCoherenceLED->setStyleSheet("QLabel { border-radius: 10px; background-color: green; }");
}

void Lights::highCoherenceOn(){
    highCoherenceLED->setStyleSheet("QLabel { border-radius: 10px; background-color: blue; }");
}

void Lights::allOff(){
    inProgressLED->setStyleSheet("QLabel { border-radius: 10px; background-color: gray; }");
    lowCoherenceLED->setStyleSheet("QLabel { border-radius: 10px; background-color: gray; }");
    midCoherenceLED->setStyleSheet("QLabel { border-radius: 10px; background-color: gray; }");
    highCoherenceLED->setStyleSheet("QLabel { border-radius: 10px; background-color: gray; }");
}






