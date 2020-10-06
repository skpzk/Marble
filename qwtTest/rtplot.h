#ifndef rtplot_h_
#define rtplot_h_

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <QApplication>
#include <QKeyEvent>
#include <iostream>
#include <QString>
#include <QTimer>
#include <string.h>

class RtPlot : public QwtPlot{
    public:
        RtPlot();
        QwtPlotCurve *curve=NULL;
        void plot(float* X, float* Y, int size);
        void getNewData();
        
    protected Q_SLOTS:
        void onTimerEvent(RtPlot*);
    private:
        int i=0;
        bool eventFilter(QObject*, QEvent*);
        QPolygonF convertTableForPlot(float* tableX, float* tableY, int size);
        QTimer *timer;
};

#endif