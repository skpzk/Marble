#include "window.h"

#include <unistd.h> // test pwd
#include <iostream>
#include <iomanip>
#include <QStyleOptionButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QStatusBar>
#include <QFileDialog>
#include <filesystem>
namespace fs = std::filesystem;

#include "state.h"


Window::Window(QWidget *parent) :
QMainWindow(parent)
{
    
    QGridLayout *grid = new QGridLayout;

    grid->addWidget(createOscSection(), 1, 0, 1, 3); //row, col, rowspan, colspan
    grid->addWidget(createFilterSection(), 1, 3, 1, 2);
    grid->addWidget(createEnvSection(), 2, 0, 1, 4);
    grid->addWidget(createMainSection(), 2, 4, 1, 1);
    grid->addWidget(createModulationMatrixSection(), 1, 5, 2, 2);
    grid->addWidget(createTitle(), 0, 0, 1, 7);

    //maybe useless
    for(int i=0; i<7; i++){
        grid->setColumnStretch(i, 1);
    }

    QPushButton * button= new QPushButton("set osc freq = 50");
    connect(button, &QPushButton::released, this, &Window::setOscFreq);
    // grid->addWidget(button, 2, 4, 1, 1);

    
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(grid);

    setWindowTitle(tr("Test interface for marble"));
    // resize(480, 320);
    
    //create filter for events
    this->installEventFilter(this);
    statusBar = QMainWindow::statusBar();
    this->setStatusBar(statusBar);

    createMenuBar();
    
    this->setStyleSheet("background-color: #1e1e1e;"
        "color: #4ec9b0;"
        "color: #569cd6;"
        "color: #e8e8e8;"
        );

    statusBar->setStyleSheet( 
        "QStatusBar{"
        "border-top: 1px solid #414141;"
        "background-color: #252525;"
        "}"
        "QSizeGrip{"
        "background-color: transparent;"
        "}"
    );

    menuBar->setStyleSheet(
        "QMenuBar{background-color: #252525;}"
        "QMenuBar::item:selected { background-color: #604e69b0; }"
        "QMenu{background-color: #252525;}"
        "QMenu::item:selected { background-color: #304e69b0; }"
    );
}

void Window::createMenuBar(){
    menuBar = QMainWindow::menuBar();
    setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));

    QAction *newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    // connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAct);

    QAction *saveAct = new QAction(tr("&Save configuration"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save configuration to file"));
    connect(saveAct, &QAction::triggered, this, &Window::saveConf);
    fileMenu->addAction(saveAct);

    QAction *saveAsAct = new QAction(tr("&Save configuration as..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save configuration to a new file"));  
    connect(saveAsAct, &QAction::triggered, this, &Window::saveConfAs);
    fileMenu->addAction(saveAsAct);

    QAction *loadAct = new QAction(tr("&Load configuration"), this);
    // loadAct->setShortcuts();
    loadAct->setStatusTip(tr("Load configuration from file"));
    connect(loadAct, &QAction::triggered, this, &Window::loadConf);
    fileMenu->addAction(loadAct);

    optionsMenu = menuBar->addMenu(tr("&Options"));

    QAction *autosaveAct = new QAction(tr("&Auto save"), this);
    // loadAct->setShortcuts();
    autosaveAct->setCheckable(true);
    autosaveAct->setStatusTip(tr("Save state on application quit."));
    
    // connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    optionsMenu->addAction(autosaveAct);

    QMenu *helpMenu = menuBar->addMenu(tr("&Help"));

    QAction *aboutAct = new QAction(tr("&About..."), this);
    // loadAct->setShortcuts();
    aboutAct->setStatusTip(tr("About application."));
    // connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    helpMenu->addAction(aboutAct);

    // optionsMenu->setStyleSheet( //ne fonctionne pas :/
        // "QMenu::icon:unchecked{color: red; width:50px; height:50px;}"
        // "QMenu::icon:checked {" /* appearance of a 'checked' icon */
        // "background: red;"
        // "border: 1px inset blue;"
        // "position: absolute;"
        // "top: 1px;"
        // "right: 1px;"
        // "bottom: 1px;"
        // "left: 1px;"
        // "};"
    // );
}

QGroupBox *Window::createOscSection(){
    QStringList titles = {"freq", "interp", "fold"};
    string paramPrefix = "osc";
    string paramNames[] = {"freq", "interp", "fold"};

    return this->createSection("Osc section", 3, titles, paramPrefix, paramNames);
}

QGroupBox *Window::createEnvSection(){
    QStringList titles = {"A", "D", "S", "R"};
    string paramPrefix = "env";
    string paramNames[] = {"A", "D", "S", "R"};

    return this->createSection("Env section", 4, titles, paramPrefix, paramNames);
}

QGroupBox *Window::createFilterSection(){
    QStringList titles = {"Fc", "Q"};
    string paramPrefix = "filter";
    string paramNames[] = {"Fc", "Q"};

    return this->createSection("Filter section", 2, titles, paramPrefix, paramNames);
}

QGroupBox *Window::createMainSection(){
    QStringList titles = {"Vol"};
    string paramPrefix = "";
    string paramNames[] = {"vol"};

    return this->createSection("Main section", 1, titles, paramPrefix, paramNames);
}

QGroupBox *Window::createTitle(){
    QGroupBox *groupBox = new QGroupBox();
    groupBox->setStyleSheet("QGroupBox{"    
        // "border-width: 0px;"
        "border: 1px solid transparent;"
        "}"
        );

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setMargin(0); 
    hbox->setSpacing(0); 

    QString title = 
    "<html><head/><body><p>"
        "<span style=' font-size:50pt;'>Marble </span>"
        // "<span style=' '/>"
        "<span style=' font-size:14pt;'>version 0.x</span>"
    "</p></body></html>";
        
    QLabel * label = new QLabel(title);
    // label->setFixedHeight(20);
    label->setStyleSheet("color:#717171;");

    hbox->addWidget(label);

    groupBox->setLayout(hbox);
    return groupBox;
}

QGroupBox *Window::createModulationMatrixSection(){
    string paramPrefix = "modulation";
    string sectionTitle = "Modulation Matrix section";

    QGroupBox *groupBox = new QGroupBox(tr(sectionTitle.c_str()));
    groupBox->setStyleSheet("QGroupBox{"
        // "background-color: #000000;" 
        // "color:#FFFFFF;"
        "border: 1.5px solid #414141;"
        "border-radius: 7px; "
        "padding: 10px; padding-top: 10px}"
        "QGroupBox::title{subcontrol-origin: margin;"
        "padding: 0 3px;"
        "background-color: transparent;"
        "}");

    QWidget * dummy = new QWidget(this);


    QGridLayout *grid = new QGridLayout;

    int rows = 10;
    int cols = 7;

    dummy->setFixedHeight(20 * (rows + 1));
    dummy->setFixedWidth(30 * cols + 50);

    QString defaultInput("input");
    QString defaultModulator("mod");

    QLabel * label = new QLabel("Target");
    label->setFixedHeight(20);

    QFont font = label->font();
    font.setPointSize(8);
    font.setBold(true);
    label->setFont(font);
    grid->addWidget(label, 0, 0);

    for(int i=1; i<rows; i++){
        QLabel * label = new QLabel(defaultInput);
        label->setFixedHeight(20);
        label->setStyleSheet("color : #818181;");
        QFont font = label->font();
        font.setPointSize(8);
        font.setBold(true);
        label->setFont(font);
        grid->addWidget(label, i, 0);
    }

    for(int j=1; j<cols; j++){
        QLabel * label = new QLabel(defaultModulator);
        label->setFixedHeight(20);

        QFont font = label->font();
        font.setPointSize(7);
        font.setBold(true);
        label->setFont(font);
        grid->addWidget(label, 0, j);
    }

    for(int i=1; i<rows; i++){
        
        for(int j=1; j<cols; j++){
            CustomSlider * slider = new CustomSlider(this);

            // slider->sizeHint(20);

            slider->setStyleSheet(
                "QSlider{"
                    "height: 20;"
                    "width: 30;"
                "}"
            );
            string paramName = std::to_string(i) + "." + std::to_string(j);
            slider->param = new StateParameter(paramName);
            slider->param->setDial(slider);

            slider->setValue(64 * ((float)j/cols-(float)i/rows));
            grid->addWidget(slider, i, j);
            grid->setColumnStretch(j, 0);

            connect(slider, &QSlider::valueChanged, this, &Window::printDial);
        }
    }

    grid->setColumnStretch(0, 10);
    
    dummy->setLayout(grid);
    QHBoxLayout * hbox = new QHBoxLayout;
    hbox->addStretch(1);
    hbox->addWidget(dummy);
    hbox->addStretch(1);
    groupBox->setLayout(hbox);
    return groupBox;
}



QGroupBox *Window::createSection(string sectionTitle, int NbDials, QStringList titles,
    string paramPrefix, string* paramNames)
{
    QGroupBox *groupBox = new QGroupBox(tr(sectionTitle.c_str()));
    groupBox->setStyleSheet("QGroupBox{"
        // "background-color: #000000;" 
        // "color:#FFFFFF;"
        "border: 1.5px solid #414141;"
        "border-radius: 7px; "
        "padding: 10px;" 
        "padding-top: 10px"
        "}"
        "QGroupBox::title{"
        "subcontrol-origin: margin;"
        "padding: 0 3px;"
        "background-color: #00000000;"
        "}"
        );
    // groupBox->setMargin(0); 
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setMargin(0); 
    hbox->setSpacing(0); 

    CustomDial **dials = new CustomDial*[NbDials];

    for(int i=0; i<NbDials; i++){
        // dials[i] = new MidiDial(this);
        dials[i] = new CustomDial(this);
        // dials[i]->setFixedWidth(40);
        dials[i]->setStyleSheet(
            // "background-color: red;" 
            // "color: #DDDDDD;"
            "qproperty-knobMargin: 20;"
            "qproperty-fixedSize: 50;");

        dials[i]->setText(titles[i]);
        string paramName = paramPrefix + "." + paramNames[i];
        dials[i]->param = new StateParameter(paramName);
        dials[i]->param->setDial(dials[i]);

        dials[i]->setValue(*dials[i]->param);

        
        hbox->addWidget(dials[i], Qt::AlignLeft);

        connect(dials[i], &QDial::valueChanged, this, &Window::printDial);
    }
    groupBox->setLayout(hbox);
    return groupBox;
}

bool Window::eventFilter(QObject *object, QEvent *ev)
{
    if (ev->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = (QKeyEvent*)ev;

        if(keyEvent->key() == Qt::Key_Q)
        {
            QApplication::quit();
        }else{
            // cout << "Key pressed : " << keyEvent->text().toStdString() <<"\n";
        }
    }
    return false;
}

void Window::printDial(int value){
    // cout<<"Dial value = "<<value<<"\n";
    char message[200];
    sprintf(message, "Dial value = %d", value);
    if(statusBar!=NULL)    statusBar->showMessage(tr(message), 1000);
}

void Window::setOscFreq(){
    StateParameter * param = new StateParameter("osc.freq");
    *param = 50;
}

void Window::saveConf(){
    
    State* state = StateParameter::state;
    if(!state->defaultsavePath.empty()){
        // cout << "Saving conf ...\n";
        state->saveConf();
        // cout << "done.\n";
    }else{
        saveConfAs();
    }
}

void Window::saveConfAs(){
    State* state = StateParameter::state;
    QString dir = QString::fromStdString(state->configDir);
    QString filePathQString = QFileDialog::getSaveFileName(this, tr("Save configuration to file"),
                           dir,
                           tr("Config files (*.cfg)"));
    // cout << "File path = " << filePathQString.toStdString() << endl;

    fs::path filePath = filePathQString.toStdString();
    // std::cout << "File path is " << filePath << '\n';

    if(filePath.has_filename()){
        // If filename does not end with .cfg, append it to file path
        filePath.replace_extension(".cfg");
        // std::cout << "File path is " << filePath << '\n';
        // Write conf to file

        state->saveConf(filePath);
    }

}

void Window::loadConf(){
    State* state = StateParameter::state;
    QString dir = QString::fromStdString(state->configDir);
    QString filePathQString = QFileDialog::getOpenFileName(this, tr("Load configuration from file"),
                           dir,
                           tr("Config files (*.cfg)"));
    // cout << "File path = " << filePathQString.toStdString() << endl;

    fs::path filePath = filePathQString.toStdString();
    // std::cout << "File path is " << filePath << '\n';

    if(filePath.has_filename()){
        // Load conf
        state->getConf(filePath);
    }

}
