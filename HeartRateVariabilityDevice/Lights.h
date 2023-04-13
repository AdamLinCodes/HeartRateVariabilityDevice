#ifndef LIGHTS_H
#define LIGHTS_H


#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>

class Lights : public QGraphicsView {
    Q_OBJECT

    public:
        Lights(QWidget* parent = nullptr);
        virtual ~Lights();

        void setupLEDs();

        void inProgressOn();
        void lowCoherenceOn();
        void midCoherenceOn();
        void highCoherenceOn();
        void allOff();

    private:
        QGridLayout* LEDLayout;
        QLabel* inProgressLED;
        QLabel* lowCoherenceLED;
        QLabel* midCoherenceLED;
        QLabel* highCoherenceLED;
};


#endif // LIGHTS_H
