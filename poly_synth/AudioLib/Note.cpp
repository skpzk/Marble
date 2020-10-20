#include "Note.h"

Note::Note(){
  this->note = -1;
  this->order = -1;
  this->channel = new SynthChannel();
}

void Note::on(int midinote){
    this->channel->activate(midinote);
    this->note = midinote;
}

void Note::off(int midinote){
    this->channel->deactivate();
}

bool Note::isActive(){
  return this->channel->isActive();
}