#include <iostream>
#include <QApplication>

#include "math.h" 
#include "window.h"
#include "plot.h"

using namespace::std;


int main(int argc, char **argv)
{
    QApplication app( argc, argv );

    // Window window; //use the example window
    // window.show();

    const int RATE = 44100, CHUNK = 256;

    float X[CHUNK];
    float Y[CHUNK];

    float freq=220.;

    for(int i=0; i<CHUNK; i++){
        X[i] = (float) i/RATE;
        Y[i] = sin(2 * M_PI * freq * X[i]);
    }

    int size = CHUNK; //Just a reminder that size doesn't need to be const

    Plot plot;
    plot.setTitle("Plot sine wave");
    plot.plot(X, Y, size);
    plot.show();

    return app.exec();
}