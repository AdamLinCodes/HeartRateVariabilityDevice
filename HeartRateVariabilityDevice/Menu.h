#ifndef MENU_H
#define MENU_H

#include <QComboBox>

class Menu : public QComboBox {
    Q_OBJECT

    public:
        Menu(QWidget* parent = nullptr);
        virtual ~Menu();
};


#endif // MENU_H
