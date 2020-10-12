#include "keys.h"

int arrowKeys(QKeyEvent* keyEvent, bool print){
    switch(keyEvent->key()){
        case Qt::Key_Left:
        case Qt::Key_Down:
            if(print) cout << "Left or down arrow key pressed\n";
            return -1;
            break;

        case Qt::Key_Right:
        case Qt::Key_Up:
            if(print) cout << "Right or up arrow key pressed\n";
            return 1;
            break;

        default:
            return 0;
            break;
    }

}


bool specialKeys(QKeyEvent* keyEvent, bool print){
    switch(keyEvent->key()){
        // case Qt::Key_Enter: //enter key and enter key next to keypad
        // case Qt::Key_Return:
        //     if(print) cout << "Enter key pressed\n";
        //     break;
        case Qt::Key_Shift:
            if(print) cout << "Shift key pressed\n";
            break;
        case Qt::Key_Meta: //windows key on win, ctrl key on macos
        case Qt::Key_Super_L: //win key on linux (left/right)
        case Qt::Key_Super_R:
            if(print) cout << "Meta modifier key pressed\n";
            break;
        case Qt::Key_Alt:
        case Qt::Key_AltGr:
            if(print) cout << "Alt modifier key pressed\n";
            break;
        case Qt::Key_Control:
            if(print) cout << "Ctrl modifier key pressed\n";
            break;
        case Qt::Key_CapsLock:
        case Qt::Key_NumLock:
        case Qt::Key_ScrollLock:
            if(print) cout << "Some lock key pressed\n";
            break;
        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
        case Qt::Key_End:
        case Qt::Key_Home:
            if(print) cout << "Some pgdUp/down/end/home key is pressed\n";
            break;
        case Qt::Key_Print:
        case Qt::Key_SysReq:
        case Qt::Key_Clear:
            if(print) cout << "Some other obscure key is pressed\n";
            break;
        case Qt::Key_Tab:
            if(print) cout << "Tab key pressed\n";
            break;
        case Qt::Key_Left:
            if(print) cout << "left arrow\n";
            break;
        
        default:
            return false; // no special key
    }
    if(print) cout << "is a special key\n";
    return true; // a special key is pressed

}

void printKey(QKeyEvent* keyEvent){

    if(!specialKeys(keyEvent, true)){
    cout << "Key pressed : " << keyEvent->text().toStdString() <<"\n";
    cout << "Virtual key : " << keyEvent->nativeVirtualKey() << "\n";
    cout << "        key : " << keyEvent->key() << "\n";
    cout << "modifiers   : " << keyEvent->modifiers() << "\n";
    }
}
