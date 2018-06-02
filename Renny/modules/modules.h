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

struct Triangle {
	float hypotenuse;
	float opposite;
	float adjacent;
};

void autododge(object* myPlayer, const spellCastDataBase* currentSpellData);

void autoComboer(object* myPlayer);

void orbwalker(object* myPlayer);

float resetDelay(float delay);
