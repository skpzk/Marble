#ifndef audioobject_h_
#define audioobject_h_
#include <iostream>
#include "../AudioAPI/AudioConstants.h"

class AudioObject{
public:
    bool isOn = false;

    virtual void on();
    virtual void off();
    void setInput(AudioObject*);
    virtual void output(void*, bool, bool);

protected:
	bool has_input=false;
    AudioObject* input = NULL;
};
#endif
