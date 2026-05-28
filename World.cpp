#include "World.h"
#include "Integrator.h"
#include <raylib.h>
#include <raymath.h>
#include "GravityEffector.h"

Vector2 World::gravity = { 0, 9.8f };

void World::Step(float dt)
{
	for (Effector* effector : effectors) {
		effector->Apply(bodies);
	}
	for (int i = 0; i < 4; i++) {
		UpdateCollision();
	}
	for (Body& body : bodies) body.AddForce(gravity * body.gravityScale, ForceMode::Acceleration);

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		for (Body& body : bodies) {
			Vector2 direction = GetMousePosition() - body.position;
			if (Vector2Length(direction) <= 100.0f) {
				Vector2 force = Vector2Normalize(direction) * -200000;

			}

		}

		DrawCircleLinesV(GetMousePosition(), 100.0f, WHITE);
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
}

void World::AddBody(const Body& body)
{
	bodies.push_back(body);
}

void World::AddEffector(Effector* effector)
{
	effectors.push_back(effector);
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
			body.position.y = boundsMax.y + body.size;
			body.velocity.y = -body.velocity.y * body.restitution;
			// body position y
			// body velocity y
		}
	}
}
