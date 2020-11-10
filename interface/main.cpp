#include <iostream>
#include <QApplication>
#include <QStyleFactory>
#include "Gui/window.h"

#include "MidiApi/Midi.h"
#include "Gui/state.h"
#include "AudioLib/osc.h"

using namespace::std;

// !: top priority
// -: to be done
// +: done 
// ?: don't know what i meant
// x: don't do this/changed my mind

/* To do list:    
    classe MidiDial / custom dial
    + avec un label et un affichage de la valeur
    + affichage de la valeur dans une barre d'état ? tooltip ?
    + double click reset
    - shift + click fine tune
    + les dials peuvent être stackés dans une hbox
    - vérifier les marges des dials pour avoir un alignement
    - enlever les fonctions non nécessaires knob margin, etc

    matrice de modulation:
    + réécrire mouse event click
    - click + shift/alt : ajustement fin ?
    - améliorer présentation : 
        + ajouter les noms des inputs/outputs
        - ajuster la taille du grid layout dans matrix section pour mieux fitter les labels
        - ajuster pour le nom des inputs
    + double click pour reset
    - deux fois double click : retrouver valeur précédente
    - changer les couleurs de inputs et diminuer la taille de la police des in/out
    - les cc sont monopolaires et les mods sont bipol, adapter le code pour ça

    Midi
    + possibilité de choisir quel CC avec un middle click
    - ajouter un bouton pour configurer tous les paramètres midi
    - ajouter un menu contextuel sur les dials/sliders pour définir le CC

    Configuration
    + configuration file
    + cf beatrix : filter.fc = 26, etc
    + finir d'implémenter save as
    + utiliser filesystem pour les paths, dans le getcwd de state et les endroits pertinents dans fileio
    + écrire un exemple d'utilisation
    - il y a une option autosave dans la barre de menu qui ne sert à rien pour l'instant : décider qu'en faire
    - il y a une option New dans la barre de menu : réinitialiser les paramètres du synthé

    Window
    + faire hériter window de QMainWindow
    + ajouter un titre
    - diminuer taille de la police des titres de section
*/

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    Midi midi;
    midi.open(0); //open port 0

    State* state = StateParameter::state;
    state->getConf();

    StateParameter s("test");
    StateParameter t("test");
    s = 15;
    cout << "Value of s is : "<< s << endl;
    cout << "Value of t is : "<< t << endl;

    Osc osc;
    

    Window window;
    window.show();

    cout<<"Test interface\n";
    // state->print();

    app.exec();

    state->autosave();
    return 0;
}