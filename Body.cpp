#include "Body.h"

void Body::Step(float dt)
{
	// update;

}

void Body::Draw()
{
	DrawCircleV(position, size, RED);
	DrawCircleLinesV(position, size, BLUE);
}

void Body::AddForce(Vector2 force, ForceMode forcemode)
{
	if (bodyType != BodyType::Dynamic) return;

	switch (forcemode)
	{
	case ForceMode::Force:
		acceleration += force * inverseMass;
		break;
	case ForceMode::Impulse:
		velocity += force * inverseMass;
		break;
	case ForceMode::Acceleration:
		acceleration += force;
		break;
	case ForceMode::VelocityChange:
		velocity += force;
		break;
	default:
		break;
	}
}
