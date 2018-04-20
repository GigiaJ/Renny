#pragma once
#include "../operations.h"

struct Slope {
	float numerator;
	float denominator;
	float gradient = numerator / denominator;
};

void autododge(object* myPlayer);

void autoComboer(object* myPlayer);

void orbwalker(object* myPlayer);

float resetDelay(float delay);
