#include "Button.h"
#include <QDebug>

Button::Button(QWidget* parent) : QPushButton(parent), m_count(0) {
  connect(this, &Button::clicked, this, &Button::onButtonClicked);
}

Button::Button(const QString& text, QWidget* parent) : QPushButton(text, parent), m_count(0) {
  connect(this, &Button::clicked, this, &Button::onButtonClicked);
  name = text;
  qDebug() <<name;
}

Button::~Button() {}

void Button::onButtonClicked() {
  m_count++;
  emit clickedWithCount(m_count, name);
}


