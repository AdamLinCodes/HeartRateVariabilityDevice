#include "Menu.h"

Menu::Menu(QWidget* parent) : QComboBox(parent) {
    addItem("Start Session");
    addItem("Settings");
    addItem("Logs/History");
}

Menu::~Menu() {
    // destructor
}
