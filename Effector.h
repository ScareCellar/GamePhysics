#pragma once
#include <vector>
#include "body.h"

class Effector {
public:
	Effector(Vector2 position, float size) : position{ position }, size{ size } {}
	virtual void Apply(std::vector<Body>& bodies) = 0;
	virtual void Draw();

	void CollectCollidingBodies(std::vector<Body>& ibodies, std::vector<Body*>& obodies);
protected:
	Vector2 position;
	float size;
};