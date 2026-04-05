#include <iostream>
#include "raylib.h"
#include "spaceship.h"
#include "lasers.h"
#include "game.h"

int main()
{
	int windowWidth = 750;
	int windowHeight = 700;
	InitWindow(windowWidth, windowHeight, "Space Invaders");
	SetTargetFPS(60);
	Color background = { 29,29,29,255 };
	Game game;
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(background);
		game.draw();
		game.handleInput();
		game.update();
		EndDrawing();
	}

	CloseWindow();
}
