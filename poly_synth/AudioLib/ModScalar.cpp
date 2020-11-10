#include "ModScalar.h"

#include <iostream>
using namespace::std;

ModScalar::ModScalar()
{
	this->value = 0;
	// cout << "value = " << value << endl;
	this->modulator = NULL;
	this->modulated = false;
}

void ModScalar::setValue(float value)
{
	this->value = value;
}

void ModScalar::setModulator(AudioObject* modulator)
{
	this->modulator = modulator;
	this->modulated = true;
}

void ModScalar::removeModulator()
{
	this->modulator = NULL;
}

float ModScalar::getValue()
{
	return this->value;
}

float* ModScalar::getValueBuffer()
{
	// float buffer[FRAMES_PER_BUFFER]; //buffer is declared in class synopsis
	sample_t mod_values[FRAMES_PER_BUFFER];

	if (this->modulated) {
		this->modulator->output(mod_values, false, false);
		for (int i = 0; i < FRAMES_PER_BUFFER; i++) {
			buffer[i] = ((float)mod_values[i] / MAX) * this->value;
		}
	}
	else {
		for (int i = 0; i < FRAMES_PER_BUFFER; i++) {
			buffer[i] = this->value;
		}
	}

	return buffer;
}