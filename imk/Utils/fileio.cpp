#include "fileio.h"

void getConfigurationFromFile(CalibrationData* calData){
    ifstream f;
    f.open ("Config/Default.cfg");
    string defaultFile;
    if(f.is_open()){ //replace everywhere with f.is_open()
        getline(f,defaultFile);
        while(isAComment(defaultFile, false)) getline(f,defaultFile); //ignore comments
        // cout << "defaultFile : " << defaultFile <<"\n";
        f.close();
        if(defaultFile.size() < 2){
            cout << "No data on Default.cfg\n";
            defaultFile = "Custom";
            
            writeToDefaultFile();
        }
        ifstream conf;
        defaultFile = "Config/" + defaultFile + ".cfg";
        // cout << "Configuration file, path :" << defaultFile <<"\n";
        conf.open(defaultFile);
        if(conf.is_open()){
            int i=-1, j=0;
            bool endWhile = false;
            string line;
            getline(conf, line);
            while(!conf.eof() && !endWhile){ // could use a do/while here
                
                
                if(!isAComment(line, false)){
                    // cout << "here" <<endl;
                    if(line.compare(0, 3, "Row")==0){
                        // cout<<"It's a row line\n";
                        i++;
                        j=0;
                    }else if(isNumeric(line)){
                        int key = stoi(line); //hopefully nothing goes wrong here
                        // cout << "key = " << key<<endl;
                        if(i<MAX_ROWS && j < MAX_KEYS_PER_ROW){
                            calData->setKey(i, j, key);
                            j++;
                        }else{
                            cout << "Error reading configuration file : too many keys\n";
                            endWhile = true;
                        }
                    }else{
                        // cout<<"not numeric\n";
                    }
                }
                getline(conf, line);
            }
            // printCalData();
            conf.close();
        }else{
            cout << "Error opening configuration file : no file\n";
            conf.close();
        }
        
    }else{
        cout <<"error opening file\nError: " << strerror(errno)<<"\n";
        f.close();
        writeToDefaultFile();
    }    
}

void writeConfigurationToFile(CalibrationData* calData){
    // char cwd[1024];
    // chdir("..");
    // getcwd(cwd, sizeof(cwd));
    // printf("Current working dir: %s\n", cwd);
    ofstream f;
    // cout << "opening file\n";
    f.open ("Config/Custom.cfg");
    if(f.is_open()){
        cout << "Saving data to Config/Custom.cfg... ";
        calData->exportCalData(&f);
        cout << "done.\n";
    }else{
        cout <<"error opening file\n";
    }
    f.close();
    // printCalData();
}

void writeToDefaultFile(){
    writeToDefaultFile((string) "");
}

void writeToDefaultFile(string s){
    if(s == ""){
        s = "Custom";
    }
    fstream f;
    f.open ("Config/Default.cfg");
    string line;
    getline(f,line);
    int numLinesToSkip = 0;
    while(isAComment(line, false)){getline(f,line);numLinesToSkip++;}
    f.clear();
    f.seekg(0);
    for(int i=0; i<numLinesToSkip; i++){getline(f,line); cout << line;}
    f << s << "\n";
    f.close();
}


bool isAComment(string s, bool print){
    if(print) cout << "line : " << s << "\n";
    int i=0;
    while(s[i] == ' ' || s[i] == '\t'){
        if(s[i] == ' ')  cout<<"space ";
        if(s[i] == '\t') cout<<"tab ";
        
        i++;
        if(i>=s.size()){
            if(print) cout <<"not a comment, blank line\n";
            return true;
        }
    }
    if(s[i] == '#'){
        if(print) cout <<"comment\n";
        return true;
    }else{
        if(print) cout << "Not a comment\n";
        return false;
    }
}

bool isNumeric(string str) {
   for (int i = 0; i < str.length(); i++)
      if (isdigit(str[i]) == false)
         return false; //when one non numeric value is found, return false
      return true;
}