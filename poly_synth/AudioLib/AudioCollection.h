#ifndef audiocollection_h_
#define audiocollection_h_

#include "../AudioAPI/AudioConstants.h"
#include "./Oscs.h"
#include "Vca.h"

class AudioCollection{
	public:
		int addElement(Vca*);
		int removeElement(void*);
		void output(void*, bool);
		int numOfElements=0;
	private:
		Vca* vcas[VOICES];
		int numOfOscs = 0;
		int numOfVcas = 0;
};

#endif
