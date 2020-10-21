#include "Modulator.h"

Modulator::Modulator(SynthChannel* channel)
{
	this->lfOsc = new Osc(1.);
	this->lfOsc->selectWaveShape(0);
	this->ampEnv = new Env();
	this->env = new Env();
	this->amp = &channel->osc->amplitude;
	this->interp = &channel->osc->interpModulation;
}

void Modulator::modulate(modType type, modValue value)
{
	switch (type) {
	case ampEnvelope:
		this->applyAmpEnv(value);
		break;
	case envelope:
		this->applyEnv(value);
		break;
	case lfo:
		this->applyLfo(value);
		break;
	}
}

void Modulator::applyAmpEnv(modValue value)
{
	switch (value) {
	case amplitude:
		this->amp->setModulator(this->ampEnv);
		break;
	case interpolation:
		this->interp->setModulator(this->ampEnv);
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

void Modulator::setADSR(modType env, float* adsr) {
	switch (env) {
	case envelope:
		this->env->setA(adsr[0]);
		this->env->setD(adsr[1]);
		this->env->setS(adsr[2]);
		this->env->setR(adsr[3]);
		break;
	case ampEnvelope:
		this->ampEnv->setA(adsr[0]);
		this->ampEnv->setD(adsr[1]);
		this->ampEnv->setS(adsr[2]);
		this->ampEnv->setR(adsr[3]);
		break;
	}
}

void Modulator::on()
{
	this->ampEnv->on();
	this->env->on();
}

void Modulator::off()
{
	this->ampEnv->off();
	this->env->off();
}

bool Modulator::isActive()
{
	// Amp envelope is the one we control for release
	return this->ampEnv->isActive;
}

