#include "DragEffector.h"

void DragEffector::Apply(std::vector<Body>& ibodies)
{
	std::vector<Body*> bodies;
	CollectCollidingBodies(ibodies, bodies);

	for (auto& body : bodies) {
		Vector2 direction = body->position - position;
		Vector2 force = (body->velocity * -1) * forceMagnitude;
		body->AddForce(force);
	}
}

void DragEffector::Draw()
{
	Effector::Draw();
	DrawCircleV(position, size, Fade(BLACK, 0.1f));
}
