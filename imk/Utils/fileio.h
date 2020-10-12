#ifndef fileio_h_
#define fileio_h_

#include <iostream>
#include <fstream>
#include <string>  
#include <cstring>

#include "defs.h"
#include "calibrationData.h"

using namespace::std;

void getConfigurationFromFile(CalibrationData*);
void writeConfigurationToFile(CalibrationData*);
void writeToDefaultFile(string s);
void writeToDefaultFile();

bool isAComment(string, bool);
bool isNumeric(string);

#endif