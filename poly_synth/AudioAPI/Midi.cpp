//*****************************************//
//  cmidiin.cpp
//  by Gary Scavone, 2003-2004.
//
//  Simple program to test MIDI input and
//  use of a user callback function.
//
//*****************************************//

#include <iostream>
#include <cstdlib>

#include "Midi.h"

void printMidiMessage(double deltatime, std::vector< unsigned char > *message){
  unsigned int nBytes = message->size();
  for ( unsigned int i=0; i<nBytes; i++ ){
    std::cout << "Byte " << i << " = " << std::hex << (int)message->at(i) << ", ";
  }
  if ( nBytes > 0 )
    std::cout << "stamp = " << deltatime << std::endl;
}

void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
  // Voices* voices = (Voices*) userData;
  AudioPatch* patch = (AudioPatch*) userData;
  // printMidiMessage(deltatime, message);

  char bytes[2];
  sprintf(bytes, "%x", (int)message->at(0)); //Midi messages are easier to decode in hexa
  //upper 4 bits are event type
  //lower 4 bits are channel #

  if(bytes[0]=='9'){//note on event
    if((int) message->at(2) != 0){ //if volume > 0
      std::cout << "Note On " << (int)message->at(1) << std::endl;
      // voices->on((int)message->at(1));
      patch->on((int)message->at(1));
    }
    else{ //if volume == 0, treat note on as a note off
      std::cout << "Note Off " << (int)message->at(1) << std::endl;
      // voices->off((int)message->at(1));
      patch->off((int)message->at(1));
    }
  }else if(bytes[0]=='8'){//note off event
    std::cout << "Note Off " << (int)message->at(1) << std::endl;
    // voices->off((int)message->at(1));
    patch->off((int)message->at(1));
  }
  else if(bytes[0]=='b'){//cc event
    std::cout << "CC " << (int)message->at(1) << ", value = " << (int)message->at(2) << std::endl;
    patch->cc((int)message->at(1), (int)message->at(2));
  }
  

}

// This function should be embedded in a try/catch block in case of
// an exception.  It offers the user a choice of MIDI ports to open.
// It returns false if there are no ports available.
int Midi::open(int portNumber){
	
	RtMidiIn *midiin = 0;

	try {
		// RtMidiIn constructor
		midiin = new RtMidiIn();
		this->midiin = midiin;
		
		if(portNumber < 0){
			// Call function to select port.
			if ( !this->chooseMidiPort() ) this->close();
		}else{
			try{
				midiin->openPort( portNumber );
			}catch ( RtMidiError &error ) {
				error.printMessage();
				this->close();
			}
		}

		// Set our callback function.  This should be done immediately after
		// opening the port to avoid having incoming messages written to the
		// queue instead of sent to the callback function.
		midiin->setCallback( &mycallback, this->patch);
        // midiin->setCallback( &mycallback, mycallback );

		// Don't ignore sysex, timing, or active sensing messages.
		midiin->ignoreTypes( false, false, false );
		

		} catch ( RtMidiError &error ) {
			error.printMessage();
			this->close();
		}
	return 0;
}

int Midi::close(){
	delete this->midiin;
	return 0;
}


bool Midi::chooseMidiPort()
{
  std::cout << "\nWould you like to open a virtual input port? [y/N] ";

  std::string keyHit;
  std::getline( std::cin, keyHit );
  if ( keyHit == "y" ) {
    this->midiin->openVirtualPort();
    return true;
  }

  std::string portName;
  unsigned int i = 0, nPorts = this->midiin->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No input ports available!" << std::endl;
    return false;
  }

  if ( nPorts == 1 ) {
    std::cout << "\nOpening " << this->midiin->getPortName() << std::endl;
  }
  else {
    for ( i=0; i<nPorts; i++ ) {
      portName = this->midiin->getPortName(i);
      std::cout << "  Input port #" << i << ": " << portName << '\n';
    }

    do {
      std::cout << "\nChoose a port number: ";
      std::cin >> i;
    } while ( i >= nPorts );
    std::getline( std::cin, keyHit );  // used to clear out stdin
  }

  
  try{
    this->midiin->openPort( i );
	}catch ( RtMidiError &error ) {
    error.printMessage();
    this->close();
  }
  return true;
}
