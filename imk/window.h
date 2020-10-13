#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QApplication>
#include <QKeyEvent>
#include <iostream>
#include <QString>
#include <string.h>
#include <QObject>
#include <QFrame>
#include <fstream>
#include <string>   

#include "MidiApi/Midi.h"
#include "Utils/keys.h"
#include "Utils/defs.h"
#include "Utils/fileio.h"
#include "Utils/calibrationData.h"


using namespace::std;



class PushButton : public QPushButton{
    Q_OBJECT
    protected:
        bool event(QEvent *e) override; //propagate arrow key events to window class
    public:
        explicit PushButton(const char*, QWidget *parent = 0);
        
};
class Window : public QWidget
{
    Q_OBJECT
    public:
        explicit Window(QWidget *parent = 0);
        void setMidi(Midi*);
    private:
        PushButton *cal_sec_button, *cal_main_button;
        PushButton *switch_layout_button;
        PushButton *cancel_calibration_button;
        bool eventFilter(QObject*, QEvent*);

        bool calibrating = false;
        CalibrationData *calData;
        kbdLayout layout=isomorphic;
        bool computeNote(int i, int j, int* returnNote);

        //midi stuff
        void noteOn(int);
        void noteOff(int);
        int baseNote = 60;
        int intervalRight = 1;
        int intervalUpLeft = 3;
        int octave = 0;
        int numberOfRows=0;
        void getNbRows();

        Midi* midi;
        bool has_midi=false;


    public slots:
        void calibrate();
        void endCalibration();
        void switchKbdLayout();
        void cancelCalibration();
};

#endif // WINDOW_H