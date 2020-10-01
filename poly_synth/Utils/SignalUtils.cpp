#include "SignalUtils.h"

float trim(float f, int minvalue, int maxvalue){
    if(f<minvalue){
        return minvalue;
    }else if(f > maxvalue){
        return maxvalue;
    }
    return f;
}

float trim(float f, int maxvalue){
    return trim(f, 0, maxvalue);
}