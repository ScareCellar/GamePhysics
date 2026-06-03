#include "World.h"
#include "Integrator.h"
#include <raylib.h>
#include <raymath.h>
#include "GravityEffector.h"
#include "Spring.h"

//Vector2 World::gravity = { 0, 9.8f };

void World::Step(float dt)
{
	for (Effector* effector : effectors) {
		effector->Apply(bodies);
	}
	for (Spring*& spring : springs) 
		spring->Apply();
	for (int i = 0; i < 4; i++) {
		UpdateCollision();
	}
	for (Body& body : bodies) {
		body.AddForce(gravity * body.gravityScale, ForceMode::Acceleration);
		SemiImplicitEuler(body, dt);
	}

	for (Body& body : bodies) body.acceleration = Vector2{ 0,0 };
}

void World::Draw()
{
	for (Effector*& effector : effectors) {
		effector->Draw();
	}
	for (Body& body : bodies) {
		body.Draw();
	}
	for (Spring*& spring : springs) spring->Draw();
}

void World::AddBody(const Body& body)
{
	bodies.push_back(body);
}

void World::AddEffector(Effector* effector)
{
	effectors.push_back(effector);
}

void World::AddSpring(Body* bodyA, Body* bodyB, float restlength, float stiffness)
{
	Spring* spring = new Spring(bodyA, bodyB, restlength, stiffness);

	springs.push_back(spring);
}

Body* World::GetBodyIntersect(const Vector2& position)
{
	for (Body& body : bodies) {
		if (CheckCollisionPointCircle(position, body.position, body.size)) {
			return &body;
		}
	}
	return nullptr;
}

void World::UpdateCollision() {
	contacts.clear();
	CreateContacts(bodies, contacts);
	SeparateContacts(contacts);
	ResolveContacts(contacts);

	// collision
	// somehow have to convert this to screen positions.
	for (auto& body : bodies)
	{
		if (body.position.x + body.size > boundsMax.x)
		{
			body.position.x = boundsMax.x - body.size;
			// set body velocity x with restitution
			body.velocity.x = -body.velocity.x * body.restitution;
		}
		if (body.position.x - body.size < boundsMin.x)
		{
			body.position.x = boundsMin.x + body.size;
			body.velocity.x = -body.velocity.x * body.restitution;
			// set body velocity x with restitution
		}
		if (body.position.y + body.size > boundsMax.y)
		{
			body.position.y = boundsMax.y - body.size;
			body.velocity.y = -body.velocity.y * body.restitution;
			// body velocity y
		}
		if (body.position.y - body.size < boundsMin.y)
		{
			body.position.y = boundsMin.y + body.size;
			body.velocity.y = -body.velocity.y * body.restitution;
			// body position y
			// body velocity y
		}
	}
}
