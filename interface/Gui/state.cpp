#include "state.h"

#include "../Utils/fileio.h"

StateParameter::StateParameter(){}

StateParameter::StateParameter(string n){
    // cout << "constructor called, name = " << n <<endl;
    // cout << "State ptr = " << &state <<endl;
    name = n;
    state->getParameterValue(this);
    state->addParameter(this);
}

void StateParameter::operator=(float v){
    value = v;
    state->addParameter(this);
}

void StateParameter::operator=(StateParameter s){
    value = s.value;
    state->addParameter(this);
}

StateParameter::operator float() const{
    return value;
}

void StateParameter::setDial(CustomDial* d){
    dial = d;
}

void StateParameter::setDial(CustomSlider* s){
    slider = s;
}

void StateParameter::warnDial(float value){
    if(dial != NULL) dial->setValue(value);
    if(slider != NULL) slider->setValue(value);
    if(callback != NULL) callback(value);
}


void StateParameter::setValue(float f){
    value = f;
    state->warn(this);
}

State::State(){
    // get the path of config files
    // the main program must run in build directory for this to work

    fs::path tmpcwd = fs::current_path();

    configDir=tmpcwd.parent_path()/"Config"; 
    autosavePath = configDir/"Autosave.cfg";
    configFile = configDir/"Conf.cfg";
    getDefaultSavePath(this);

}

void State::warn(StateParameter* p){
    
    string name = p->name;
    for(int i=0; i<data.size();i++){
        //test if name is in data vector
        if(name.compare(data.at(i)->name) == 0){    
            for(int j=0; j<data.at(i)->params.size();j++){
                if(!(data.at(i)->params.at(j) == p)){ 
                    //if the ptr is not the calling ptr
                    //warn all the pointers that the value has changed
                    data.at(i)->params.at(j)->value = p->value;
                    data.at(i)->params.at(j)->warnDial(p->value);
                }
                
                
            }
            data.at(i)->value = p->value;  
        }
    
    }
    // print();
}

void State::addParameter(StateParameter* p){
    addParameter(p, true);
}

void State::addParameter(StateParameter* p, bool addPtr){
    // cout << "State::addParameter called\n";
    
    string name = p->name;
    //test if name is already in data vector
        //if true, change value of StateData
            //test if the ptr to StateParameter is already in the pointers vector
                //if true, do nothing
                //if false, add ptr to vector
            //warn all the pointers that the value has changed
        //if false, add new StateData
    bool found=false;
    for(int i=0; i<data.size();i++){
        //test if name is already in data vector
        if(name.compare(data.at(i)->name) == 0){
            found = true;
            //test if the ptr to StateParameter is already in the pointers vector
            bool ptrFound = false;
            for(int j=0; j<data.at(i)->params.size();j++){
                if(data.at(i)->params.at(j) == p){
                    ptrFound = true;
                }
                //warn all the pointers that the value has changed
                data.at(i)->params.at(j)->value = p->value;
                data.at(i)->params.at(j)->warnDial(p->value);
            }
            if(ptrFound){
                //if true, do nothing
            }else{
                //if false, add ptr to vector
                if(addPtr) data.at(i)->params.push_back(p);
            }
            //update value of data
            // cout << "updating value of data : name = " << data.at(i)->name;
            // cout << ", value = " << p->value << endl;
            data.at(i)->value = p->value;

            
        }
    
    }
    if(!found){
        //if false, add new StateData
        // cout <<"not found\n";
        StateData* tmpdata = new StateData;
        tmpdata->name = p->name;
        tmpdata->value = p->value;
        tmpdata->params.push_back(p);
        data.push_back(tmpdata);
    }

    // print();
}

void State::getParameterValue(StateParameter* p){
    // cout << "State::getParameter called\n";
    
    string name = p->name;
    bool found=false;
    for(int i=0; i<data.size();i++){
        //test if name is already in data vector
        if(name.compare(data.at(i)->name) == 0){
            found = true;
            p->value = data.at(i)->value;         
        }
    }
    if(!found){
        p->value = 0;
    }
    // print();
}

void State::print(){
    cout << "**** State ****" << endl;
    for(int i=0; i<data.size();i++){
        cout << "Param " <<data.at(i)->name;
        cout << " = " << data.at(i)->value<<endl;
    }
    cout << "***************" << endl;
}

void State::getConf(){
    // cout << "getting Conf" << endl;
    getConfigurationFromFile(this);
}

void State::getConf(fs::path loadPath){
    // cout << "getting Conf" << endl;
    setDefaultSavePath(loadPath, this);
    getConfigurationFromFile(loadPath, this);
}

void State::saveConf(){
    // cout << "saving Conf" << endl;
    writeConfigurationToFile(this->defaultsavePath, this);
}

void State::autosave(){
    // cout << "saving Conf" << endl;
    writeConfigurationToFile(this->autosavePath, this);
}

void State::saveConf(fs::path savePath){
    // cout << "saving Conf" << endl;
    setDefaultSavePath(savePath, this);
    writeConfigurationToFile(this->defaultsavePath, this);
}

void State::exportState(ofstream* f){
    *f << "#Configuration\n";
    for(int i=0; i<data.size(); i++){
        if(data.at(i)->midiCC != -1){
            *f << "midi." << data.at(i)->name << "=" << data.at(i)->midiCC << "\n";
        }
    }    
    for(int i=0; i<data.size(); i++){
        *f << data.at(i)->name << "=" << data.at(i)->value << "\n";
    }
}

void State::ccUpdate(int cc, int value){
    if(!settingCC){
        // cout << "not setting cc\n";
        for(int i=0; i<data.size();i++){
            if(data.at(i)->midiCC == cc){
                for(int j=0; j<data.at(i)->params.size();j++){
                    //warn all the pointers that the value has changed
                    data.at(i)->params.at(j)->value = value;
                    data.at(i)->params.at(j)->warnDial(value);
                }
                data.at(i)->value = value;
            }
        }
    }else{
        // cout << "setting cc\n";
        for(int i=0; i<data.size();i++){
            if(data.at(i)->midiCC == cc){ // if cc is already used, remove previous use
                data.at(i)->midiCC = -1;
            }
            if(ccParamName.compare(data.at(i)->name) == 0){
                for(int j=0; j<data.at(i)->params.size();j++){
                    //warn all the pointers that the value has changed
                    data.at(i)->params.at(j)->value = value;
                    data.at(i)->params.at(j)->warnDial(value);
                }
                data.at(i)->value = value;
                data.at(i)->midiCC = cc;
            }
        }
        settingCC = false;
        ccParamName = ""; 
    }
}

void State::ccChoosing(string name){
    settingCC = true;
    ccParamName = name;
    cout << "State listening to cc events...\n";
}

void State::setCC(string name, int cc){
    settingCC = true;
    ccParamName = name;
    ccUpdate(cc, 0);
}