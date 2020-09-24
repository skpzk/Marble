
#include "Voices.h"

#include <stdlib.h>
#include <stdio.h>

Voices::Voices(int number){
  this->total_voices = number;

  this->notes = new Note*[number]; 
  
  if(notes==NULL){
    for(int i = 0; i< 10 ; i++){
      printf("Error allocating memory for voices\n");
    }
  }else{
    for(int i = 0; i< this->total_voices ; i++){
      this->notes[i] = new Note();
      this->mixer.addInput(&this->notes[i]->va);
    }
  }

  this->voice = -1;

}

void Voices::printVoices(){
  printf("*****Voices*****\n");
  for(int i=0; i<this->total_voices; i++){
    
    if(this->notes[i]->isActive()){
      printf("Note %d, ordre = %d\n", this->notes[i]->note, this->notes[i]->order);
    }
    
  }
  printf("****************\n");
}

void Voices::on(int midinote){
  printf("Voices::on\n");
  this->printVoices();
  if(!this->is_note_played(midinote)){ //si la note n'est pas déjà jouée, on la joue
    this->voice = this->find_free_voice();
    this->notes[this->voice]->on(midinote);
    this->notes[this->voice]->order = this->find_last_order()+1;
  }
  else{//sinon, on redémarre l'enveloppe et on met à jour l'ordre
    this->voice = this->find_stop_voice(midinote);
    this->notes[this->voice]->on(midinote);
    this->update_order(midinote);
    this->notes[this->voice]->order = this->find_last_order()+1;
  }
  this->printVoices();
}
void Voices::off(int note){//on arrête l'enveloppe (qui passe en decay), mais on laisse la note dans la liste tant que l'enveloppe est active
  printf("Voices::off\n");
  this->voice = this->find_stop_voice(note);
  if(this->voice != -1){
    //note off
    notes[this->voice]->off(note);
    //notes[voice]->note =-1;//si on décommente, update_status ne fonctionne pas
  }
  this->printVoices();
}
void Voices::update_status(){//on détecte les enveloppes inactives, on enlève les notes de la liste et on met à jour l'ordre
  int n = 0;
  for(int i = 0; i< this->total_voices ; i++){
    if(!this->notes[i]->isActive() && this->notes[i]->note != -1){//l'env est inactive mais la note n'est pas supprimée
      this->notes[i]->note = -1;
      n = this->notes[i]->order ;
      this->notes[i]->order = -1;
      update_order(n);
      printf("Update status\n");
    }
  }
}

// void Voices::connectToMixer(AudioMixerP* MixerP){
//   for(int i = 0; i< this->total_voices ; i++){
//     this->cords[i] = new AudioConnection(this->notes[i]->out, 0, *MixerP->Mixer, i);
//   }
// }
////////// Midi CC //////////
void Voices::setWaveform(int w){
  /* 0 : WAVEFORM_SINE
   * 1 : WAVEFORM_SAWTOOTH
   * 2 : WAVEFORM_TRIANGLE
   * 3 : WAVEFORM_SQUARE
   */
  if((w>=0)&&(w<4)){
    for(int i=0; i<this->total_voices; i++){
      this->notes[i]->setWaveform(w);
    }
  }
  else{
    printf("Wrong waveform type\n");
  }
}
void Voices::setAmplitude(float f){
  if((f>=0)&&(f<=2)){
    for(int i=0; i<this->total_voices; i++){
      //this->notes[i]->out.gain(f); //is it the right parameter to change ??? //or main Mixer.gain ?
      this->notes[i]->amp = f;
    }
  }
  else{
    printf("Wrong amplitude\n");
  }
}

////////// Private methods //////////

bool Voices::is_note_played(int note){ //kind of a duplicate of find_stop_voice
  for(int i = 0; i< this->total_voices ; i++){
    if(this->notes[i]->note == note){
      return true ;
    }
  }
  return false;
}

int Voices::find_stop_voice(int note){ //called when a midi note off is received
  for(int i = 0; i< this->total_voices ; i++){
    if(this->notes[i]->note == note){
      return i; //On retourne la voix correspondant à la note à arrêter
    }
  }
  return -1; //Si la voix n'existe pas, on ne fait rien
}

int Voices::find_free_voice(){
  for(int i = 0; i< this->total_voices ; i++){
    if(this->notes[i]->note == -1){
      return i; // Si la voix est libre, on retourne celle-là
    }
  }
  for(int i = 0; i< this->total_voices ; i++){
    if(this->notes[i]->order == 0){
      update_order(0);
      return i; //Si aucune voix est libre, on retourne la première voix jouée et on ajuste l'ordre
    }
  }
  return 0; //par sûreté.
}

void Voices::update_order(int n){//On vient d'enlever la note jouée au rang n, on met à jour l'ordre des autres notes
  for(int j = 0; j<this->total_voices ; j++){
    if(this->notes[j]->order>n){
      this->notes[j]->order -=1;
    }
  }
}

int Voices::find_last_order(){
  int o = -1;
  for(int i = 0; i< this->total_voices ; i++){
    if(this->notes[i]->order > o){
      o = this->notes[i]->order;
    }
  }
  return o;
}