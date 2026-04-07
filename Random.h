#pragma once
#include "raylib.h"
#include <raymath.h>
class Random {
public:
	inline static float GetRandomFloat(float max) {
		return GetRandomValue(0, 1000) / 1000.0f;
	}

	inline static float GetRandomFloat(float min, float max) {
		return GetRandomValue(min * 1000, max * 1000) / 1000.0f;
	}
};