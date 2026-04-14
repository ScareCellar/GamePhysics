/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <vector>
//#include <math.h>
#include "raylib.h"
#include <raymath.h>
#include <string>
#include "../World.h"
#include "../Body.h"
#include "../Random.h"
#include "../GravityEffector.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir



int main()
{
	World scene;
	//GravityEffector* effector = new GravityEffector(10000);
	//scene.AddEffector(new GravityEffector(100));
	
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Physics timestep
	float timeAccum = 0.0f;
	float fixedTimeStep = 1.0f / 60.0f;
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{

		std::string fpsText = "FPS: " + std::to_string(GetFPS());
		DrawText(fpsText.c_str(), 100, 100, 20, RED);
		float deltaTime = GetFrameTime();
		Vector2 mousePosition = GetMousePosition();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
			Body body;
			body.position = mousePosition;
			body.velocity = Vector2{ 0,0 };
			body.size = Random::GetRandomFloat(5.0f, 20.0f);
			float angle = Random::GetRandomFloat(1.0f) * (2 * PI);
			Vector2 direction;
			direction.x = cosf(angle);
			direction.y = sinf(angle);
			body.restitution = 1.0f;
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
				body.bodyType = BodyType::Dynamic;
				body.velocity.x = direction.x * (Random::GetRandomFloat(1.0f) * 500);
				body.velocity.y = direction.y * (Random::GetRandomFloat(1.0f) * 500);
			}
			else {
				body.bodyType = BodyType::Static;
			}
			
			body.acceleration = Vector2{ 0,0 };
			body.size = 2.0f + Random::GetRandomFloat(1.0f) * 20.0f;
			body.gravityScale = 0.0f;
			body.mass = body.size;
			body.inverseMass = 1 / body.mass;

			scene.AddBody(body);
		}
		

		

		// UPDATE
		timeAccum += GetFrameTime();
		while (timeAccum > fixedTimeStep) {
			
			scene.Step(fixedTimeStep);
			timeAccum -= fixedTimeStep;
		}

		DrawCircleV(mousePosition, 5, DARKPURPLE);
		
		// DRAW
		scene.Draw();
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

