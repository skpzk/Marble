#ifndef plot_h_
#define plot_h_

#include "../AudioAPI/AudioConstants.h"
#include "../AudioLib/AudioOutput.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <QApplication>
#include <QKeyEvent>
#include <iostream>
#include <QString>
#include <QTimer>
#include <string.h>

class Plot : public QwtPlot{
    public:
        Plot();
        QwtPlotCurve *curve=NULL;
        void plot(float* X, float* Y, int size);
        void plot(float* Y, int size);
        void plot(sample_t* Y, int size);
        void getNewData();

        void setInput(AudioOutput*);
        
    protected Q_SLOTS:
        void onTimerEvent(Plot*);
    private:
        int i=0;
        bool has_input=false;
        AudioOutput* input;
        bool eventFilter(QObject*, QEvent*);
        QPolygonF convertTableForPlot(float* tableX, float* tableY, int size);
        QTimer *timer;
        sample_t inBuffer[FRAMES_PER_BUFFER];
};

#endif