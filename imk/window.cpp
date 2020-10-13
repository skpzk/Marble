#include "window.h"

#include <unistd.h> // test pwd

PushButton::PushButton(const char* text, QWidget *parent)
    : QPushButton(text, parent) {}

bool PushButton::event(QEvent *e) {
    QPushButton::event(e);
    return QObject::event(e);}

Window::Window(QWidget *parent) :
QWidget(parent)
{
    setFixedSize(400, 100);
    chdir("..");

    calData = new CalibrationData();
    getConfigurationFromFile(calData);
    numberOfRows = calData->getNbRows();

    // Create and position buttons
    cal_main_button = new PushButton("Calibrate main keyboard", this);
    cal_main_button->setGeometry(10, 10, 180, 30);
    cal_sec_button = new PushButton("Calibrate shift keyboard", this);
    cal_sec_button->setGeometry(10, 50, 180, 30);

    switch_layout_button = new PushButton("Switch to classic kbd layout", this);
    switch_layout_button->setGeometry(210, 10, 180, 30);

    cancel_calibration_button = new PushButton("Cancel calibration", this);
    cancel_calibration_button->setGeometry(210, 50, 180, 30);

    connect(cal_main_button, SIGNAL (released()), this, SLOT (calibrate()));
    connect(switch_layout_button, SIGNAL (released()), this, SLOT (switchKbdLayout()));
    connect(cancel_calibration_button, SIGNAL (released()), this, SLOT (cancelCalibration()));


    //create filter for events
    this->installEventFilter(this);
}


bool Window::eventFilter(QObject *object, QEvent *ev)
{
    int errNb;
    
    if (ev->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = (QKeyEvent*)ev;

        if(arrowKeys(keyEvent, true)!=0){
            octave += arrowKeys(keyEvent, false);
            if(octave >6) octave=6;
            if(octave <-5) octave=-5;
        }
        else if (!keyEvent->isAutoRepeat()){
            if(this->calibrating){
                cout<<"Calibrating :";
                errNb = calData->addKey(keyEvent);
                if(errNb == -1) endCalibration();
            }else{
                this->noteOn(keyEvent->key());
            }
        }
    }
    if (ev->type() == QEvent::KeyRelease)
    {
        QKeyEvent* keyEvent = (QKeyEvent*)ev;
        if (!keyEvent->isAutoRepeat()){
            if(!this->calibrating){
                this->noteOff(keyEvent->key());
            }
        }
    }
    return false;
}

void Window::calibrate(){
    // give output on what user should do ?

    cout<<"Calibrating...\n";
    calibrating = true;
    calData->startCalibration();
    cal_main_button->setText("End calibration");
    calData->init();
    disconnect(cal_main_button, SIGNAL (released()), this, SLOT (calibrate()));
    connect(cal_main_button, SIGNAL (released()), this, SLOT (endCalibration()));
}

void Window::endCalibration(){
    calibrating = false;
    calData->endCalibration();
    cal_main_button->setText("Calibrate main keyboard");
    disconnect(cal_main_button, SIGNAL (released()), this, SLOT (endCalibration()));
    connect(cal_main_button, SIGNAL (released()), this, SLOT (calibrate()));
    numberOfRows = calData->getNbRows();
    if(numberOfRows == 0){
        cout << "New calibration is empty, loading old calibration data...";
        getConfigurationFromFile(calData);
        numberOfRows = calData->getNbRows();
        cout << "done.\n";

    }else{
        writeConfigurationToFile(calData);
    }
}

void Window::cancelCalibration(){
    calibrating = false;
    calData->endCalibration();
    cal_main_button->setText("Calibrate main keyboard");
    disconnect(cal_main_button, SIGNAL (released()), this, SLOT (endCalibration()));
    connect(cal_main_button, SIGNAL (released()), this, SLOT (calibrate()));
    cout << "Cancelling calibration...";
    getConfigurationFromFile(calData);
    numberOfRows = calData->getNbRows();
    cout << "done.\n";
}

void Window::switchKbdLayout(){
    if(layout==isomorphic){
        switch_layout_button->setText("Switch to iso kbd layout");
        layout = traditional;
    }else{
        switch_layout_button->setText("Switch to classic kbd layout");
        layout = isomorphic;
    }
}

void Window::setMidi(Midi* midi){
    this->midi = midi;
}

bool Window::computeNote(int i, int j, int* returnNote){
    int note;
    switch(layout){
        case isomorphic:
            note = baseNote + (numberOfRows-1-i) * intervalUpLeft + j*intervalRight;
            note = note + octave*12;
            *returnNote = note;
            return true;
            break;
        case traditional:
            int row = (numberOfRows-1-i);
            int whiteKeys[] = {0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 24};
            int blackKeys[] = {0, 1, 3, 0, 6, 8, 10, 0,  13, 15, 0,  18, 20, 22, 0 };
            if(row%2 == 0){
                note = baseNote + ((int) row/2) * 12 + whiteKeys[j];
                note = note + octave*12;
                *returnNote = note;
                return true;
            }else{
                int offset = blackKeys[j];
                if(offset==0) return false;
                note = baseNote + ((int) row/2) * 12 + offset;
                note = note + octave*12;
                *returnNote = note;
                return true;
            }
            break;

    }
    return false;
}

void Window::noteOn(int key){
    bool print=false;
    int position[2], i, j;
    if(print) cout<<"NoteOn, key = "<<key<<"\n";
    if(calData->findKey(key, position)){
        i = position[0];
        j = position[1];
        if(print) cout << "position = ("<<i<<", "<<j<<")\n";
        int note;
        if(computeNote(i, j, &note)){   
            if(print) cout << "note = " << note << "\n";
            calData->setNote(i, j, note);
            midi->noteOn(note);
        }else{
            cout << "Traditional layout : ignoring this key\n";
        }
    }else{
        cout<< "key not registered\n";
    }
}

void Window::noteOff(int key){
    bool print=false;
    int position[2], i, j;
    if(print)  cout<<"NoteOff, key = "<<key<<"\n";
    if(calData->findKey(key, position)){
        i = position[0];
        j = position[1];
        if(print) cout << "position = ("<<i<<", "<<j<<")\n";

        midi->noteOff(calData->getNote(i, j));
    }else{
        cout<< "key not registered\n";
    }
}