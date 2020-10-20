#include "Modulator.h"

Modulator::Modulator(SynthChannel* channel)
{
	this->lfOsc = new Osc(1.);
	this->lfOsc->selectWaveShape(0);
	this->env = new Env();
	this->amp = &channel->osc->amplitude;
	this->interp = &channel->osc->interpModulation;
}

void Modulator::modulate(modType type, modValue value)
{
	switch (type) {
	case envelope:
		this->applyEnv(value);
		break;
	case lfo:
		this->applyLfo(value);
		break;
	}
}

void Modulator::applyEnv(modValue value)
{
	switch (value) {
	case amplitude:
		this->amp->setModulator(this->env);
		break;
	case interpolation:
		this->interp->setModulator(this->env);
		break;
	}
}

void Modulator::applyLfo(modValue value)
{
	switch (value) {
	case amplitude:
		this->amp->setModulator(this->lfOsc);
		break;
	case interpolation:
		this->interp->setModulator(this->lfOsc);
		break;
	}
}

void Modulator::setADSR(float* adsr) {
	this->env->setA(adsr[0]);
	this->env->setD(adsr[1]);
	this->env->setS(adsr[2]);
	this->env->setR(adsr[3]);
}

void Modulator::on()
{
	this->env->on();
}

void Modulator::off()
{
	this->env->off();
}

bool Modulator::isActive()
{
	return this->env->isActive;
}

