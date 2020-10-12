#include "calibrationData.h"

CalibrationData::CalibrationData(){
    init();
}

void CalibrationData::init(){
    for(int i=0; i<MAX_ROWS; i++){
        for(int j=0; j<MAX_KEYS_PER_ROW; j++){
            calKey[i][j].key = -1;
        }
    }
}

bool CalibrationData::isInCalData(QKeyEvent* keyEvent){
    for(int i=0; i<MAX_ROWS; i++){
        for(int j=0; j<MAX_KEYS_PER_ROW; j++){
            if(calKey[i][j].key == keyEvent->key()) return true;
        }
    }
    return false;
}

void CalibrationData::print(){
    for(int i=0; i<MAX_ROWS; i++){
        for(int j=0; j<MAX_KEYS_PER_ROW; j++){
            if(calKey[i][j].key != -1){
            cout << "Row "<< i << ", key "<<j<<" = "<< calKey[i][j].key << "\n";
            }
        }
    }
}

void CalibrationData::exportCalData(ofstream* f){
    *f << "Custom Configuration\n";
    for(int i=0; i<MAX_ROWS; i++){
        *f << "Row "<< i << "\n";
        for(int j=0; j<MAX_KEYS_PER_ROW; j++){
            *f << calKey[i][j].key << "\n";
        }
    }
}


bool CalibrationData::findKey(int key, int* position){
    for(int i=0; i<MAX_ROWS; i++){
        for(int j=0; j<MAX_KEYS_PER_ROW; j++){
            if(calKey[i][j].key == key){
                position[0] = i;
                position[1] = j;
                return true;
            }
        }
    }
    return false;
}

void CalibrationData::setKey(int i, int j, int key){
    calKey[i][j].key = key;
}

void CalibrationData::setNote(int i, int j, int note){
    calKey[i][j].note = note;
}

int CalibrationData::getNote(int i, int j){
    return calKey[i][j].note;
}

int CalibrationData::getNbRows(){
    numberOfRows = 0;
    for(int i=0; i<MAX_ROWS; i++){
        bool emptyRow = true;
        for(int j=0; j<MAX_KEYS_PER_ROW; j++){
            if(calKey[i][j].key != -1){
                emptyRow = false;
            }
        }
        if(!emptyRow) numberOfRows++;
    }
    return numberOfRows;
}


void CalibrationData::startCalibration(){
    cal_i = 0;
    cal_j = 0;
}

void CalibrationData::endCalibration(){
    cal_i = 0;
    cal_j = 0;
}


int CalibrationData::addKey(QKeyEvent* keyEvent){
    if(!specialKeys(keyEvent, false)){
        cout << "        key : " << keyEvent->key() << "\n";
        cout << "modifiers   : " << keyEvent->modifiers() << "\n";
        if( (keyEvent->key() == Qt::Key_Enter) || (keyEvent->key() == Qt::Key_Return)){
            cout << "Switching to new row\n";
            cal_i++;
            cal_j=0;
            return 0;
        }else if(isInCalData(keyEvent)){
            cout << "Key already pressed.\n";
            return 1;
        }
        else {
            cout << "Calibrating Key "<<cal_j<<" on row "<<cal_i<<"... "<<keyEvent->key()<<".\n";
            calKey[cal_i][cal_j].key = keyEvent->key();
            cal_j++;
            if(cal_j >= MAX_KEYS_PER_ROW){
                cout<<"Maximum number of keys for this row reached\n";
                cal_j=0;
                cal_i++;
                if(cal_i >= MAX_ROWS){
                    cout<<"Maximum number of rows reached, ending calibration.\n";
                    endCalibration();
                    return -1; //end calibration signal
                }else{
                    cout <<"Switching to next row.\n";
                    return 0;
                }
            }
            return 0;
        }
    }
    return 1; //key not added
}