/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define GUI_PHYSICS_IMPLEMENTATION
#pragma warning ( push )
#pragma warning ( disable : 4576)
#include "gui_physics.h"
#pragma warning ( pop )

#include <vector>
//#include <math.h>
#include "raylib.h"
#include <raymath.h>
#include <string>
#include "../World.h"
#include "../Body.h"
#include "../Random.h"
#include "../GravityEffector.h"
#include "../PointEffector.h"
#include "../AreaEffector.h"
#include "../DragEffector.h"
#include "../Spring.h"
#include "../world_camera.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

GuiPhysicsState state;

void AddBody(World& world, WorldCamera& camera);
void AddEffector(World& scene, WorldCamera& camera);

bool mouseOverGui;

int main()
{
	World scene;
	WorldCamera sceneCamera(Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }, 5);
	// set min (left-bottom) boundary(0, screen height) and max (right, top) boundary(screen width, 0)
	scene.SetBounds(sceneCamera.ScreenToWorld({ 0, (float)GetScreenHeight() }), sceneCamera.ScreenToWorld({ (float)GetScreenWidth(), 0 }));
	//GravityEffector* effector = new GravityEffector(10000);
	//scene.AddEffector(new GravityEffector(100));

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Get GUI state
	state = InitGuiPhysics();
	GuiLoadStyle("raygui/styles/cyber/style_cyber.rgs");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Physics timestep
	float timeAccum = 0.0f;
	bool simulate = true;

	//scene.AddEffector(new GravityEffector(Vector2{ 900, 600 }, 200, 350000.0f));
	//scene.AddEffector(new PointEffector(Vector2{ 300, 200 }, 200, 30000.0f));
	//
	//scene.AddEffector(new AreaEffector(Vector2{ 900, 200 }, 200, 30000.0f, Vector2{0,1}));
	//scene.AddEffector(new DragEffector(Vector2{ 300, 600 }, 200, 10.0f));

	Body* selectedBody = nullptr;
	Body* connectedBody = nullptr;

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		float fixedTimeStep = 1.0f / state.FPSValue;
		float deltaTime = fminf(GetFrameTime(), 0.1f);

		std::string fpsText = "FPS: " + std::to_string(GetFPS());
		DrawText(fpsText.c_str(), 100, 100, 20, RED);

		if (IsKeyPressed(KEY_SPACE)) {
			state.SimulateActive = !state.SimulateActive;
		}
		Rectangle rec{ state.anchor02.x, state.anchor02.y, 304.0f, 664.0f };
		mouseOverGui = (state.PhysicsPanelActive && CheckCollisionPointRec(GetMousePosition(), rec));
		Vector2 mousePosition =  sceneCamera.ScreenToWorld(GetMousePosition());

		if (!mouseOverGui)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ||
				(IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
			{
				if (IsKeyDown(KEY_LEFT_SHIFT))
				{
					AddEffector(scene, sceneCamera);
				}
				else
				{
					AddBody(scene, sceneCamera);
				}
			}
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
				selectedBody = scene.GetBodyIntersect(mousePosition);
			}
			if (selectedBody) {
				if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_LEFT_CONTROL)) {
					Vector2 position = mousePosition;
					Vector2 force = Spring::GetSpringForce(position, selectedBody->position, 1.0f, 3.0f);
					selectedBody->AddForce(force);
				}
			}
		}




		if (state.SimulateActive) {
			// UPDATE
			timeAccum += GetFrameTime();
			while (timeAccum > fixedTimeStep) {

				scene.Step(fixedTimeStep);
				timeAccum -= fixedTimeStep;
			}
		}
		//world.AddEffector(new GravitationEffector(Vector2{ 900, 600 }, 200, 30000.0f));

		DrawCircleLinesV(mousePosition, state.BodySizeValue, DARKPURPLE);

		if (selectedBody) {
			DrawCircleLinesV(selectedBody->position, selectedBody->size, BLUE);
		}

		// DRAW
		sceneCamera.Begin(); // set world camera
		scene.Draw(); // draw using world camera transform
		sceneCamera.End(); // remove world camera
		BeginDrawing();

		GuiPhysics(&state);

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(DARKGRAY);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

void AddBody(World& scene, WorldCamera& camera) {
	Body body;
	body.bodyType = (BodyType)state.BodyTypeActive;
	body.position = camera.ScreenToWorld(GetMousePosition());
	body.velocity = Vector2{ 0,0 };
	body.size = state.BodySizeValue;
	float angle = Random::GetRandomFloat(1.0f) * (2 * PI);
	body.restitution = 1.0f;
	Vector2 direction;
	direction.x = cosf(angle);
	direction.y = sinf(angle);

	if (body.bodyType == BodyType::Dynamic) {
		body.velocity.x = direction.x * (Random::GetRandomFloat(1.0f));
		body.velocity.y = direction.y * (Random::GetRandomFloat(1.0f));
	}
	//if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
	//	body.bodyType = BodyType::Dynamic;
	//	body.velocity.x = direction.x * (Random::GetRandomFloat(1.0f) * 500);
	//	body.velocity.y = direction.y * (Random::GetRandomFloat(1.0f) * 500);
	//}
	//else {
	//	body.bodyType = BodyType::Static;
	//}

	body.acceleration = Vector2{ 0,0 };
	body.size = state.BodySizeValue;
	body.gravityScale = state.BodyGravityValue;
	body.mass = body.size * state.BodyMassValue;
	body.inverseMass = 1 / body.mass;

	scene.AddBody(body);
}

void AddEffector(World& scene, WorldCamera& camera)
{
	Vector2 position = camera.ScreenToWorld(GetMousePosition());

	Effector* effector = nullptr;
	switch ((EffectorType)state.EffectorTypeActive)
	{
	case EffectorType::Area:
		scene.AddEffector(new AreaEffector(position, state.EffectorSizeValue, state.EffectorForceValue, Vector2{0,1}));
		break;
	case EffectorType::Drag:
		scene.AddEffector(new DragEffector(position, state.EffectorSizeValue, state.EffectorForceValue));
		break;
	case EffectorType::Gravitation:
		scene.AddEffector(new GravityEffector(position, state.EffectorSizeValue, state.EffectorForceValue));
		break;
	case EffectorType::Point:
		scene.AddEffector(new PointEffector(position, state.EffectorSizeValue, state.EffectorForceValue));
		break;
	}

	if (effector) scene.AddEffector(effector);
}

