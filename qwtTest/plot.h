#ifndef plot_h_
#define plot_h_

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <QApplication>
#include <QKeyEvent>
#include <iostream>
#include <QString>
#include <string.h>




class Plot: public QwtPlot{
    public:
        Plot();
        QwtPlotCurve *curve=NULL;
        void plot(float* X, float* Y, int size);
    private:
        bool eventFilter(QObject*, QEvent*);
        QPolygonF convertTableForPlot(float* tableX, float* tableY, int size);
};

#endif