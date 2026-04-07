#pragma once
#include <raylib.h>
#include <raymath.h>

struct Body
{
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float mass;
	float force;
	float size;
	float restitution;
	float damping = 0.1f;
	float gravityScale = 1.0f;

	void Step(float dt);

	void Draw();

	void AddForce(Vector2 force);
};

