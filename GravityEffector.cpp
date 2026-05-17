#include "GravityEffector.h"
#include <raylib.h>
#include "raymath.h"

void GravityEffector::Apply(std::vector<Body>& ibodies)
{
    std::vector<Body*> bodies;
    CollectCollidingBodies(ibodies, bodies);

    for (size_t i = 0; i < bodies.size(); i++)
    {
        for (size_t j = i + 1; j < bodies.size(); j++)
        {
            Body& bodyA = *bodies[i];
            Body& bodyB = *bodies[j];

            // STEP 1: Direction vector
            Vector2 direction = bodyA.position - bodyB.position;

            // STEP 2: Distance
            float distance = Vector2Length(direction);

            // STEP 3: Clamp distance
            //distance = Clamp(distance, 0.0f, 1.0f);
            distance = fmaxf(distance, 1.0f);

            // F = G(m1 x m2/d^2)
            // Gravitational Constant = 0.0000000000667430
            // STEP 4: Force magnitude
            float forceMagnitude = strength * ((bodyA.mass * bodyB.mass) / (distance * distance)); // <use formula in image above to compute force>;

            // STEP 5: Force vector
            Vector2 force = Vector2Normalize(direction) * forceMagnitude;//  <scale normalized direction by force magnitude>

            // STEP 6: Apply equal and opposite forces
            bodyA.AddForce(force * -1);
            bodyB.AddForce(force);
        }
    }
}

void GravityEffector::Draw()
{
    Effector::Draw();
    DrawCircleV(position, size, Fade(PURPLE, 0.2f));
}
