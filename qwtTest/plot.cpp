#include "plot.h"
#include <algorithm>    // std::min_element, std::max_element

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

    this->setAxisScale( QwtPlot::yLeft, minY - 0.1*rangeY, maxY + 0.1*rangeY );
    this->setAxisScale( QwtPlot::xBottom, minX - 0.025*rangeX, maxX + 0.025*rangeX);
}

bool Plot::eventFilter(QObject *object, QEvent *ev)
{
      if (ev->type() == QEvent::KeyPress)
      {
           QKeyEvent* keyEvent = (QKeyEvent*)ev;

           if(keyEvent->key() == Qt::Key_Q)
           {
               QApplication::quit();
           }
    }
    return false;
}