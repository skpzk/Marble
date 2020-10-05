#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QApplication>
#include <QKeyEvent>
#include <iostream>
#include <QString>
#include <string.h>

class QPushButton;
class Window : public QWidget
{
    public:
        explicit Window(QWidget *parent = 0);
    private:
        QPushButton *m_button;
        bool eventFilter(QObject*, QEvent*);
};

#endif // WINDOW_H