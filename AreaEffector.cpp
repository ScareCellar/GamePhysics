#include "AreaEffector.h"

void AreaEffector::Apply(std::vector<Body>& ibodies)
{
	std::vector<Body*> bodies;
	CollectCollidingBodies(ibodies, bodies);

	for (auto& body : bodies) {
		Vector2 force = direction * strength;
		body->AddForce(force);
	}
}

void AreaEffector::Draw()
{
	Effector::Draw();
	DrawCircleV(position, size, Fade(ORANGE, 0.2f));
}
