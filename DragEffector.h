#pragma once
#include "Effector.h"

class DragEffector : public Effector {
public:
	DragEffector(Vector2 position, float size, float forceMagnitude) :
		Effector{ position, size },
		forceMagnitude{ forceMagnitude } {
	}
	// Inherited via Effector
	void Apply(std::vector<Body>& bodies) override;
	void Draw() override;

private:

	float forceMagnitude;
};