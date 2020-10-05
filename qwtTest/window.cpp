#include "window.h"

using namespace::std;

Window::Window(QWidget *parent) :
 QWidget(parent)
 {
 // Set size of the window
 setFixedSize(100, 50);

 // Create and position the button
 m_button = new QPushButton("Hello World", this);
 m_button->setGeometry(10, 10, 80, 30);

 connect(m_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
 //create filter for events
 this->installEventFilter(this);
}

bool Window::eventFilter(QObject *object, QEvent *ev)
{
      if (ev->type() == QEvent::KeyPress)
      {
           QKeyEvent* keyEvent = (QKeyEvent*)ev;

           if(keyEvent->key() == Qt::Key_Q)
           {
               QApplication::quit();
           }else{
               cout << "Key pressed : " << keyEvent->text().toStdString() <<"\n";
           }
    }
    return false;
}