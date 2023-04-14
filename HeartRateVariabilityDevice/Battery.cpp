#include "Battery.h"

Battery::Battery(QWidget* parent) : QProgressBar(parent) {
    setMaximum(100);
    setMinimum(0);
    setValue(100);
    dead = false;
}

Battery::~Battery() {}

void Battery::losePower() {
    setValue(this->value() - 10);
    if (this->value() == 0) {
        dead = true;
    }
}
void Battery::recharge() {
    setValue(100);
    dead = false;
}

bool Battery::isDead() {
    return dead;
}
