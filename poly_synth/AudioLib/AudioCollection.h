#ifndef audiocollection_h_
#define audiocollection_h_

#include "../AudioAPI/AudioConstants.h"
#include "./Oscs.h"
#include "Va.h"

class AudioCollection{
	public:
		//int addElement(Osc*);
		int addElement(Va*);
		int removeElement(void*);
		//void listElements();
		void output(void*, bool);
		int numOfElements=0;
	private:
		//Osc** oscs;
		Va* vas[VOICES];
		int numOfOscs = 0;
		int numOfVas = 0;
};

#endif
