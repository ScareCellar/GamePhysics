#include "Body.h"

void Body::Step(float dt)
{
	// update;

}

void Body::Draw()
{
	DrawCircleV(position, size, RED);
}

void Body::AddForce(Vector2 force)
{
	acceleration += force;
}
