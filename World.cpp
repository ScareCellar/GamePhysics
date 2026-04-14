#include "World.h"
#include "Integrator.h"
#include <raylib.h>
#include <raymath.h>
#include "GravityEffector.h"



void World::Step(float dt)
{
	for (Effector* effector : effectors) {
		effector->Apply(bodies);
	}
	UpdateCollision();
	for (Body& body : bodies) {
		SemiImplicitEuler(body, dt);
		body.acceleration = gravity * body.gravityScale * 100.0f;
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		for (Body& body : bodies) {
			Vector2 direction = GetMousePosition() - body.position;
			if (Vector2Length(direction) <= 100.0f) {
				Vector2 force = Vector2Normalize(direction) * -200000;

			}

		}

		DrawCircleLinesV(GetMousePosition(), 100.0f, WHITE);
	}
}

void World::Draw()
{
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

void World::UpdateCollision() {
	contacts.clear();
	CreateContacts(bodies, contacts);
	SeparateContacts(contacts);
	ResolveContacts(contacts);

	for (Body& body : bodies)
	{
		if (body.position.x + body.size > GetScreenWidth())
		{
			body.position.x = GetScreenWidth() - body.size;
			body.velocity.x *= -1.0f;
		}
		if (body.position.y + body.size > GetScreenHeight())
		{
			body.position.y = GetScreenHeight() - body.size;
			body.velocity.y *= -1.0f;
		}
		if (body.position.x - body.size < 0.0f)
		{
			body.position.x = 0 + body.size;
			body.velocity.x *= -1.0f;
		}
		if (body.position.y - body.size < 0)
		{
			body.position.y = 0 + body.size;
			body.velocity.y *= -1.0f;
		}
		//body.position.x += body.velocity.x * dt;
		//body.position.y += body.velocity.y * dt;

	}
}
