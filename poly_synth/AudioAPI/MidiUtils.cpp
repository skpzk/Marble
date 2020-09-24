#include "MidiUtils.h"

float ftom(float f){
	//f = 440 * (2**(1/12))**(m - 69);
	float m = 69 + log(f/440.)/log(pow(2, 1./12));
	return m;
}

float mtof(float m){
	float f = 440. * pow(pow(2, 1./12), m - 69);
	return f;
}

/*
int main(){
	float m = ftom(415.3);
	printf("m = %f\n", m);
	float f = mtof(68);
	printf("f = %f\n", f);
}*/