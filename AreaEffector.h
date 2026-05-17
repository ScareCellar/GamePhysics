#pragma once
#include "Effector.h"
class AreaEffector : public Effector
{
public:
	AreaEffector(Vector2 position, float size, float strength, Vector2 direction) :
		Effector{ position, size }, strength{ strength }, direction{ direction } {
	}
	// Inherited via Effector
	void Apply(std::vector<Body>& bodies) override;

	void Draw() override;

private:
	Vector2 direction;
	float strength;
};

