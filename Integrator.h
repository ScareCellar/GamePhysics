#pragma once
#include "Body.h"


void ExplicitEuler(Body& body, float timestep) {
	body.position += body.velocity * timestep;
	body.velocity += body.acceleration * timestep;
	body.velocity *= 1.0f / (1.0f + body.damping * timestep);
}

void SemiImplicitEuler(Body& body, float timestep) {
	body.velocity += body.acceleration * timestep;
	body.position += body.velocity * timestep;
	body.velocity *= 1.0f / (1.0f + body.damping * timestep);
}
