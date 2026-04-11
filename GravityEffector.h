#pragma once
#include "Effector.h"
class GravityEffector : public Effector 
{
public:
	GravityEffector(float strength) : strength(strength) {}

	// Inherited via Effector
	void Apply(std::vector<Body>& bodies) override;

private:
	float strength;
};

