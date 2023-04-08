#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button : public QPushButton {
    Q_OBJECT

    public:
        Button(QWidget* parent = nullptr);
        Button(const QString& text, QWidget* parent = nullptr);
        virtual ~Button();

    signals:
        void clickedWithCount(int count);

    private slots:
        void onButtonClicked();

    private:
        int m_count;
};

#endif // BUTTON_H
