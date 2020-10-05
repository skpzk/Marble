#include <iostream>
#include <QApplication>
#include <QLabel>

using namespace::std;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QLabel hello("Hello world!");

    hello.show();
    cout<<"main.cpp\n";
    return app.exec();
}