#include "Button.h"
#include <QDebug>

Button::Button(QWidget* parent) : QPushButton(parent), m_count(0) {
  connect(this, &Button::clicked, this, &Button::onButtonClicked);
}

Button::Button(const QString& text, QWidget* parent) : QPushButton(text, parent), m_count(0) {
  connect(this, &Button::clicked, this, &Button::onButtonClicked);
  name = text;
}

Button::~Button() {}

void Button::onButtonClicked() {
  m_count++;
  emit clickedWithCount(m_count, name);

  switch(name.toStdString()[0]){
    //Represents the Menu button being pushed
    case 'M':
      break;
    //Represents the Start/Stop button being pushed
    case 'S':
      break;
    //Represents the Up button being pushed
    case 'U':
      break;
    //Represents the Down button being pushed
    case 'D':
      break;
    //Represents the Left button being pushed
    case 'L':
      break;
    //Represents the Right button being pushed
    case 'R':
      break;
    default:
      break;
  }
}
