#include "plot.h"
#include <algorithm>    // std::min_element, std::max_element
#include <cstdlib> //rand()
#include <math.h> //M_PI
#include <csignal>


using namespace::std;


Plot::Plot(){
    //create filter for events
    this->installEventFilter(this);
    this->setCanvasBackground( Qt::white );

    this->curve = new QwtPlotCurve();
    this->curve->setPen( Qt::blue, 1 ),
    this->curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    this->curve->attach( this );
    this->resize( 600, 400 );

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]{ onTimerEvent(this); });
    timer->start(100);
}

void Plot::onTimerEvent(Plot* plot){
    plot->i++;
    plot->getNewData();
    plot->replot();
    // cout << "onTimerEvent called, i = " << plot->i <<"\n";
}
void Plot::getNewData(){
    // cout << "Getting New Data\n";

    if(this->has_input){
        this->input->writeToBuffer(inBuffer, false, true);

        this->plot(inBuffer, FRAMES_PER_BUFFER);
    }else{
        float rangeX, rangeY;
        rangeX = FRAMES_PER_BUFFER / SAMPLE_RATE;
        rangeY = 2. * MAX;

        

        this->setAxisScale( QwtPlot::yLeft, -MAX, MAX);
        this->setAxisScale( QwtPlot::xBottom, 0 - 0.025*rangeX, rangeX + 0.025*rangeX);

    }

}

QPolygonF Plot::convertTableForPlot(float* tableX, float* tableY, int size){
    QPolygonF points;
    for(int i=0; i<size; i++){
        points << QPointF(tableX[i], tableY[i]);
    }
    

    return points;
}
void Plot::plot(float* X, float* Y, int size){
    this->curve->setSamples( this->convertTableForPlot(X, Y, size) );
    float minX=0, maxX=0, rangeX;
    float minY=0, maxY=0, rangeY;
    minX = *min_element(X,X+size);
    minY = *min_element(Y,Y+size);
    maxX = *max_element(X,X+size);
    maxY = *max_element(Y,Y+size);

    rangeX = maxX-minX;
    rangeY = maxY-minY;
    if(rangeY == 0){
        rangeY = 2;
        minY = -1;
        maxY = 1;
    }

    // this->setAxisScale( QwtPlot::yLeft, minY - 0.1*rangeY, maxY + 0.1*rangeY );
    this->setAxisScale( QwtPlot::yLeft, -MAX, MAX);
    this->setAxisScale( QwtPlot::xBottom, minX - 0.025*rangeX, maxX + 0.025*rangeX);
}

void Plot::plot(float* Y, int size){
    float X[FRAMES_PER_BUFFER];

    for(int i=0; i<FRAMES_PER_BUFFER; i++){
        
        X[i] = (float) i/SAMPLE_RATE;
    }
    this->plot(X, Y, size);
}

void Plot::plot(sample_t * Y, int size){
    float X[FRAMES_PER_BUFFER], Yfloat[FRAMES_PER_BUFFER];

    for(int i=0; i<FRAMES_PER_BUFFER; i++){
        
        X[i] = (float) i/SAMPLE_RATE;
        Yfloat[i] = (float) Y[i];
    }
    this->plot(X, Yfloat, size);
}

bool Plot::eventFilter(QObject *object, QEvent *ev)
{
      if (ev->type() == QEvent::KeyPress)
      {
           QKeyEvent* keyEvent = (QKeyEvent*)ev;

           if(keyEvent->key() == Qt::Key_Q)
           {
               QApplication::quit();
               std::raise(SIGINT);
           }
    }
    return false;
}
void Plot::setInput(AudioOutput* audioOutput){
    if(!this->has_input){
        this->input = audioOutput;
        this->has_input = true;
    }
}