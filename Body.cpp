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

void Body::AddForce(Vector2 force)
{
	if (bodyType != BodyType::Dynamic) return;
	acceleration += force;
}
