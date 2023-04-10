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
        void clickedWithCount(int count, QString& name);

    private slots:
        void onButtonClicked();

    private:
        int m_count;
        QString name;
};

#endif // BUTTON_H
