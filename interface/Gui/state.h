#ifndef state_h_
#define state_h_

#include <iostream>
#include <string>
#include <vector>

#include <fstream>
#include <iostream>

#include <filesystem>
namespace fs = std::filesystem;

class StateParameter;
#include "cdial.h"
#include "cslider.h"
// #include "osc.h"

using namespace::std;
#include <functional>
using std::placeholders::_1;

class StateParameter; // interface with program : it can be used like a float (except for declaration)
class StateData; //stores data : name, value, pointers to stateParameters that have the same name

typedef void (*StateCallback)(float);  

/*
To declare a new parameter, used eg in an Osc:
    
    //Creating parameter identified by its paramName
    //If a parameter with the same name already exists, the value of param is set to the existing value
    //If not, it gets a 0 value.
    //The parameter is then added to State
        StateParameter *param =  new StateParameter(paramName);

    //Change the value of param, and change value of all dials and parameters with the same name
        *param = 15;
    //You can also use
        param->setValue(15)
        //it changes value of all dials and parameters with the same name, 
        //but if the parameter name doesn't already exist, it is not added to State
        //and if a ptr to param if not in State, it is not added

    //The value of param can be accessed like this:
        StateParameter s("test");
        float value;
        value = s;
    
    //if you try to copy a param, like this:
        StateParameter s("test");
        StateParameter t("otherTest");
        s = 15;
        t = s;
        //only the value of s is copied to t, the name of t stays "otherTest"

To access State class, which holds all parameters:
    State* state = StateParameter::state;

If you want to create a parameter with no callback to it (eg when reading conf from file), you can use:
    StateParameter* p = new StateParameter;
    p->name = paramName; //paramName is a string
    p->value = paramValue; //paramValue is a float
    state->addParameter(p, false); //false : doesn't add parameter to the list that State holds-
*/



class State{
    public:
        void addParameter(StateParameter* p, bool addPtr);
        void addParameter(StateParameter* p);
        //add parameter to vector of params
        //if name doesn't exists, add it
        //if it exists, add ptr to dic/list
        //the pointer to StateParameter is used to change its value when necessary
        //if reading state from file, use addPtr=false
        //else, simply use addParameter(StateParameter* p)

        void getParameterValue(StateParameter* p);
        void warn(StateParameter* p);

        void getConf();
        void getConf(fs::path);
        void saveConf();
        void saveConf(fs::path);
        void autosave();


        void exportState(std::ofstream*);

        void print();

        State();

        fs::path configDir;
        fs::path autosavePath;
        fs::path configFile;
        fs::path defaultsavePath;

        void ccUpdate(int, int);//called by Midi class
        void ccChoosing(string);
        void setCC(string, int);
        //When you want to set a CC by listening to a midi message
        //(ie the first cc message received is used to set the cc number)
        //use : state->ccChoosing(paramName);

    private:

        // void readConf();
        // void writeConf();

        vector<StateData*> data;

        bool settingCC = false;
        string ccParamName = "";

};

//use vector of stateData ?
class StateParameter{
    
    private:      
        std::function<void(float)> callback=NULL;
		
    public:

        static inline State *state = new State;

        // StateData *data;
        string name;
        float value;

        // StateParameter(float);
        StateParameter(string); //when declared or changed, notify State
        StateParameter(); //does nothing

        void operator=(float);//set the value of parameter with a = operator, updates State
        void operator=(StateParameter);//copy only the value of another parameter with a = operator, updates State
        operator float() const;//returns the value of parameter

        CustomDial *dial = NULL;
        CustomSlider *slider = NULL;
        void setDial(CustomDial*);
        void setDial(CustomSlider*);
        void warnDial(float);

        
		template <typename T, typename T2>
		void setCallback(T f, T2 obj){ 
            // due to some compiling error, the function must be declared here (cf: https://bytefreaks.net/programming-2/c/c-undefined-reference-to-templated-class-function)
            callback = std::bind(f, obj, _1);
        };

        void setValue(float f);
};

struct StateData{
    string name;
    float value;
    int midiCC= -1;
    vector<StateParameter*> params;
};

#endif //#ifndef state_h_