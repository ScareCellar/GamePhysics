#pragma once
#include <vector>
#include "Body.h"
#include "Effector.h"
#include "Collision.h"
class World
{
	
public:
	World() { bodies.reserve(1000); }
	void Step(float dt);

	void Draw();

	void AddBody(const Body& body);

	void AddEffector(Effector* effector);

	void AddSpring(Body* bodyA, Body* bodyB, float restlength, float stiffness);

	void SetBounds(Vector2 min, Vector2 max) { boundsMin = min; boundsMax = max; }

	Body* GetBodyIntersect(const Vector2& position);

	void UpdateCollision();

	void SetGravity(float gravityValue) {
		gravity.y = gravityValue;
	}

private:
	Vector2 boundsMin{ -10.0f, -5.0f };
	Vector2 boundsMax{ 10.0f,  5.0f };
	Vector2 gravity{0.0f, 0.0f};

	std::vector<Body> bodies;
	std::vector<Contact> contacts;
	std::vector<Effector*> effectors;
	std::vector<class Spring*> springs;
};

