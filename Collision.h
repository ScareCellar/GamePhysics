#pragma once
#include "Body.h"
#include <vector>
struct Contact {
	Body* bodyA;
	Body* bodyB;

	float restitution;
	float depth;
	Vector2 normal;
};

bool Intersects(const Body& bodyA, const Body& bodyB);
void CreateContacts(std::vector<Body>& bodies, std::vector<Contact>& contacts);
void SeparateContacts(std::vector<Contact>& contacts);
void ResolveContacts(std::vector<Contact>& contacts);