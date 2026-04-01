/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <vector>
//#include <raymath.h>
#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

struct Body
{
	Vector2 position;
	Vector2 velocity;
	float mass;
	Vector2 acceleration;
	float force;
	float size;
	float restitution;
};

float GetRandomFloat()
{
	return GetRandomValue(0, 1000) / 1000.0f;
}

Vector2 gravity{ 0, 9.81f };

int main()
{
	std::vector<Body> bodies;
	bodies.reserve(1000);
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		float deltaTime = GetFrameTime();
		Vector2 mousePosition = GetMousePosition();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Body body;
			body.position = mousePosition;
			body.velocity = Vector2{ 500,0 };
			body.size = GetRandomValue(5, 20);
			float angle = GetRandomFloat() * (2 * PI);
			Vector2 direction;
			direction.x = cosf(angle);
			direction.y = sinf(angle);
			body.restitution = 1.0f;

			body.velocity = direction * (GetRandomFloat() * 500);
			body.size = 2.0f + GetRandomFloat() * 20.0f;

			bodies.push_back(body);
		}

		for (Body& body : bodies)
		{
			if (body.position.x + body.size > GetScreenWidth())
			{
				body.position.x = GetScreenWidth() - body.size;
				body.velocity.x *= -1.0f;
			}
			if (body.position.y + body.size > GetScreenHeight())
			{
				body.position.x = GetScreenWidth() - body.size;
				body.velocity.x *= -1.0f;
			}
			if (body.position.x - body.size < 0.0f)
			{
				body.position.x = 0 + body.size;
				body.velocity.x *= -1.0f;
			}
			if (body.position.y - body.size < 0)
			{
				body.position.x = 0 + body.size;
				body.velocity.x *= -1.0f;
			}
			body.position.x += body.velocity.x * deltaTime;
			body.position.y += body.velocity.y * deltaTime;
		}

		// UPDATE
		DrawCircleV(mousePosition, 5, DARKPURPLE);

		for (const Body& body : bodies)
		{
			DrawCircleV(body.position, body.size, RED);
		}

		// DRAW
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200, 200, 20, WHITE);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
