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
	static Vector2 gravity;
public:
	void Step(float dt);

	void Draw();

	void AddBody(const Body& body);

	void AddEffector(Effector* effector);

	void SetBounds(Vector2 min, Vector2 max) { boundsMin = min; boundsMax = max; }

	Body* GetBodyIntersect(const Vector2& position);

	void UpdateCollision();

private:
	Vector2 boundsMin{ -10.0f, -5.0f };
	Vector2 boundsMax{ 10.0f,  5.0f };
};

