#pragma once
#include <vector>
#include "Body.h"
#include "Effector.h"
#include "Collision.h"
class World
{
	std::vector<Body> bodies;
	std::vector<Contact> contacts;
	std::vector<Effector*> effectors;
	Vector2 gravity = { 0.0f, 1.0f };
public:
	void Step(float dt);

	void Draw();

	void AddBody(const Body& body);

	void AddEffector(Effector* effector);

	void UpdateCollision();
};

