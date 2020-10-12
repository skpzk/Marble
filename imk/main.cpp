#include <iostream>
#include <QApplication>
#include "window.h"

#include "MidiApi/Midi.h"

using namespace::std;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Midi midi;
    midi.open(0); //open port 0

    Window window;
    window.setMidi(&midi);
    window.show();

    cout<<"Isomorphic midi keyboard.cpp\n";
    return app.exec();
}