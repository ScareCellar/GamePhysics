#include "Effector.h"

void Effector::Draw() {
	DrawCircleLinesV(position, size, WHITE);
}

void Effector::CollectCollidingBodies(std::vector<Body>& ibodies, std::vector<Body*>& obodies)
{
	for (Body& body : ibodies) {
		if (Vector2DistanceSqr(body.position, this->position) < (size * size)) {
			obodies.push_back(&body);
		}
	}
}
