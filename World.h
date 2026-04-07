#pragma once
#include <vector>
#include "Body.h"
class World
{
	std::vector<Body> bodies;
	Vector2 gravity = { 0.0f, 1.0f };
public:
	World() {
		//unpointer thyself fiend
	}

	void Step(float dt);

	void Draw();

	void AddBody(const Body& body);
};

