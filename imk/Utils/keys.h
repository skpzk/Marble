#ifndef keys_h_
#define keys_h_

#include <QKeyEvent>
#include <iostream>

using namespace::std;

int arrowKeys(QKeyEvent*, bool);
bool specialKeys(QKeyEvent*, bool);
void printKey(QKeyEvent*);

#endif
