#include <iostream>
#include "raylib.h"
#include "spaceship.h"
#include "lasers.h"
#include "game.h"

int main()
{
	Color yellow = { 243, 216, 27, 255 };
	int windowWidth = 750;
	int windowHeight = 700;
	int offset = 50;
	InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Space Invaders");
	Font font = LoadFontEx("assets/monogram.ttf", 64, 0, 0);
	Texture2D spaceshipTexture = LoadTexture("assets/spaceship.png");
	SetTargetFPS(60);
	Color background = { 29,29,29,255 };
	Game game;
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(background);
		DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, yellow);
		DrawLineEx({25,730}, {775,730}, 3, yellow);
		if (game.run)
		{
			for (int i = game.lives; i > 0; --i)
			{
				DrawTexture(spaceshipTexture, 40 + (i - 1) * 55, 740, WHITE);
			}
			DrawTextEx(font, "SPACE INVADERS", {500, 740}, 32, 2, yellow);
		}
		else
		{
			DrawTextEx(font, "GAME OVER", {50, 740}, 32, 2, yellow);
			DrawTextEx(font, "Press ENTER to Restart", {450, 750}, 24, 2, yellow);
		}
		game.draw();
		game.handleInput();
		game.update();
		EndDrawing();
	}

	CloseWindow();
}
