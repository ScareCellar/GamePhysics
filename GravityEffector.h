#pragma once
#include "Effector.h"
class GravityEffector : public Effector 
{
public:
	GravityEffector(Vector2 position, float size, float strength) :
		Effector { position, size }, strength{ strength } {}
	// Inherited via Effector
	void Apply(std::vector<Body>& bodies) override;

	void Draw() override;

private:
	float strength;
};

