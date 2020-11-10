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
#include <QResource>
#include <QFrame>
#include <fstream>
#include <string>   
#include <QDial>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMainWindow>

#include "../MidiApi/Midi.h"

#include "../Utils/fileio.h"

#include "cdial.h"
#include "cslider.h"



using namespace::std;

class Window : public QMainWindow
{
    Q_OBJECT
    public:
        explicit Window(QWidget *parent = 0);
        void setMidi(Midi*);
    private:

        bool eventFilter(QObject*, QEvent*);
        // int NbDials;

        QGroupBox * createSection(string sectionTitle, int nbDials, QStringList titles, string, string*);
        QGroupBox * createOscSection();
        QGroupBox * createFilterSection();
        QGroupBox * createEnvSection();
        QGroupBox * createMainSection();
        QGroupBox * createModulationMatrixSection();
        QGroupBox * createTitle();

        void createMenuBar();

        QStatusBar *statusBar=NULL;
        QMenuBar *menuBar;
        QMenu *optionsMenu ;

    public slots:
        void printDial(int);
        void setOscFreq();
        void saveConf();
        void saveConfAs();
        void loadConf();
};

#endif // WINDOW_H