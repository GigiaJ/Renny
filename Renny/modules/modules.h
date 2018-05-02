#pragma once
#include "../operations.h"

struct Slope {
	float numerator;
	float denominator;
	
	inline float getGradient() {
		return (numerator / denominator);
	}

	inline float getReciprocalGradient() {
		return (denominator / numerator);
	}
};

void autododge(object* myPlayer);

void autoComboer(object* myPlayer);

void orbwalker(object* myPlayer);

float resetDelay(float delay);
