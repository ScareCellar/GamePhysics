#pragma once
#include "raylib.h"
#include <raymath.h>
class Random {
public:
	inline static float GetRandomFloat(float max) {
		return static_cast<float>(GetRandomValue(0, max * 1000) / 1000.0f);
	}

	inline static float GetRandomFloat(float min, float max) {
		return GetRandomValue(min * 1000.0f, max * 1000.0f) / 1000.0f;
	}
};