#ifndef fileio_h_
#define fileio_h_

#include <iostream>
#include <fstream>
#include <string>  
#include <cstring>

#include <unistd.h> // pwd
#include <algorithm>
#include <filesystem>

#include "../Gui/state.h"

using namespace::std;
namespace fs = std::filesystem;

void getConfigurationFromFile(State*);
void getConfigurationFromFile(fs::path, State*);
void writeConfigurationToFile(State*);
void writeConfigurationToFile(fs::path, State*);

void getDefaultSavePath(State*);
void setDefaultSavePath(fs::path, State*);

bool isAComment(string, bool);
bool isNumeric(string);
bool hasEnding (std::string const &fullString, std::string const &ending);

#endif