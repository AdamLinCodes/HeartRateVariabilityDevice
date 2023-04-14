#ifndef BATTERY_H
#define BATTERY_H


#include <QProgressBar>

class Battery : public QProgressBar {
    Q_OBJECT

    public:
        Battery(QWidget* parent = nullptr);
        void losePower(int);
        void recharge();
        virtual ~Battery();
        bool isDead();

    private:
        bool dead;
};

#endif // BATTERY_H
