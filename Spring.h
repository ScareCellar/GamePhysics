#pragma once
#include "raylib.h"

struct Body;

class Spring {
public:
	Body* bodyA;
	Body* bodyB;

	float restingLength;
	float force;
	float damping;

	Spring() = default;
	Spring(Body* bodyA, Body* bodyB, float restingLength, float force, float damping = 1) : 
		bodyA{ bodyA }, 
		bodyB{ bodyB }, 
		restingLength{ restingLength }, 
		force{ force },
		damping{ damping }
	{ }

	void Apply(float multiplier = 1);
	void Draw();

	static Vector2 GetSpringForce(Vector2 positionA, Vector2 positionB, float restLength, float stiffness = 1);
private:

protected:

};