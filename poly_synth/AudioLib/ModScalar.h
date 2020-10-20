#include "AudioObject.h"

class ModScalar {
public:
	ModScalar();
	void setValue(float);
	void setModulator(AudioObject*);
	void removeModulator();
	float getValue();
	float* getValueBuffer();

private:
	float value;
	AudioObject* modulator;
	bool modulated;
};