//*****************************************//
//  cmidiout.cpp
//  by Gary Scavone, 2003-2004.
//
//  Simple program to test MIDI input and
//  use of a user callback function.
//
//*****************************************//

#include <iostream>
#include <cstdlib>

#include "Midi.h"

using namespace::std;


// This function should be embedded in a try/catch block in case of
// an exception.  It offers the user a choice of MIDI ports to open.
// It returns false if there are no ports available.
int Midi::open(int portNumber){
	
	RtMidiOut *midiout = 0;

	try {
		// RtMidiOut constructor
		midiout = new RtMidiOut();
		this->midiout = midiout;
		
		if(portNumber < 0){
			// Call function to select port.
			if ( !this->chooseMidiPort() ) this->close();
		}else{
			try{
				midiout->openPort( portNumber );
			}catch ( RtMidiError &error ) {
				error.printMessage();
				this->close();
			}
		}

		} catch ( RtMidiError &error ) {
			error.printMessage();
			this->close();
		}
	return 0;
}

int Midi::close(){
	delete this->midiout;
	return 0;
}

void Midi::noteOn(int note){
  std::vector<unsigned char> message;

  if(note > 127) note=127;
  if(note < 0) note=0;

  message.push_back(144); //note on
  message.push_back(note); //note
  message.push_back(127); //velocity
  midiout->sendMessage( &message );
}

void Midi::noteOff(int note){

  if(note > 127) note=127;
  if(note < 0) note=0;
  
  std::vector<unsigned char> message;
  message.push_back(128); //note off
  message.push_back(note); //note
  message.push_back(0); //velocity
  midiout->sendMessage( &message );
}

bool Midi::chooseMidiPort()
{
  std::cout << "\nWould you like to open a virtual input port? [y/N] ";

  std::string keyHit;
  std::getline( std::cin, keyHit );
  if ( keyHit == "y" ) {
    this->midiout->openVirtualPort();
    return true;
  }

  std::string portName;
  unsigned int i = 0, nPorts = this->midiout->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No input ports available!" << std::endl;
    return false;
  }

  if ( nPorts == 1 ) {
    std::cout << "\nOpening " << this->midiout->getPortName() << std::endl;
  }
  else {
    for ( i=0; i<nPorts; i++ ) {
      portName = this->midiout->getPortName(i);
      std::cout << "  Input port #" << i << ": " << portName << '\n';
    }

    do {
      std::cout << "\nChoose a port number: ";
      std::cin >> i;
    } while ( i >= nPorts );
    std::getline( std::cin, keyHit );  // used to clear out stdin
  }

  
  try{
    this->midiout->openPort( i );
	}catch ( RtMidiError &error ) {
    error.printMessage();
    this->close();
  }
  return true;
}
