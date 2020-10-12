#ifndef calibrationdata_h_
#define calibrationdata_h_

#include <QKeyEvent>
#include <fstream>
#include <iostream>

using namespace::std;

#include "defs.h"
#include "keys.h"

typedef struct{
	int key=-1;
    float note = 0;
}CalKey;

class CalibrationData{
    private:
        CalKey calKey[MAX_ROWS][MAX_KEYS_PER_ROW]; // 5 row of 15 keys should be enough
        

        bool calibrating = false;
        int cal_i=0, cal_j=0;
        int numberOfRows=0;

    public:
        CalibrationData();
        void init();

        void startCalibration();
        void endCalibration();

        CalKey getKey(int row, int column);
        int getNote(int i, int j);
        void setKey(int row, int column, int value);
        void setNote(int row, int column, int value);
        int getNbRows();

        bool isInCalData(QKeyEvent* keyEvent);
        bool findKey(int, int*);
        int addKey(QKeyEvent*);

        void exportCalData(std::ofstream*);
        void print();

};


#endif