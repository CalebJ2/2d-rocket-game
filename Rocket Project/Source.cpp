#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "Vector2Funcs.h"
#include "Object.h"
#include "Rocket.h"
#include <time.h>
#include <string>
#include <fstream>
#include "asteroid.h"
#include <vector>

using namespace std;

bool gameOver = false;
bool haveWrittenHighscore = false; // to make sure highscore isn't written every loop - CJ
int highscore = 0;
int altitude = 0;

// Write number to file - CJ
void setHighScore(int newHighscore) {
	ofstream fout;
	fout.open("highscore.txt");
	fout << newHighscore;
	fout.close();
}
// Read number from file. If file empty or doesn't exist returns 0. - CJ
int getHighScore() {
	ifstream fin;
	int line;
	fin.open("highscore.txt");
	if (fin.peek() != ifstream::traits_type::eof()) {
		fin >> line;
		fin.close();
		return line;
	}
	else {
		fin.close();
		return 0;
	}
}

int main()
{
	// Raylib setup - CJ
	// Very roughly, 1px = 1cm - CJ
	InitWindow(800, 480, "test"); // width, height, windowName - CJ
	SetTargetFPS(60);//controls how many times per second loop updates - CJ
	highscore = getHighScore();

	Rocket player({ 400,730 }, { 0,0 }, LoadTexture("./textures/spaceship.png"), LoadTexture("./textures/engine.png"), LoadTexture("./textures/flame.png"), 15000); // initialize rocket - CJ
	player.scale = 0.2f; // set size of rocket to 0.2x normal size (based on pixels of texture and pixels of window) - CJ

	Texture2D Space = LoadTexture("./textures/1.jpg"); // initialize background t - NK
	Texture2D Planet = LoadTexture("./textures/planet.png"); // initialize planet t - NK
	// initialize "camera" for 2d mode - CJ
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();
	Camera2D camera;
	camera.target = v2Sub(player.pos,makeV2(10,10)); // Makes it so camera zooms in towards player - CJ
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	// Creates vector for the asteroid - DF
	vector<asteroid> asteroids; 

	// Loads the image texture for the ateroids - DF
	Texture2D asteroidTexture=LoadTexture("./textures/Asteroid Final.png"); 
	
	while (!WindowShouldClose()) { //main game loop - CJ
		// update section - CJ
		if (IsKeyDown(KEY_R)) { // reset everything when r is pressed - CJ
			player.reset();
			gameOver = false;
			highscore = getHighScore();
			haveWrittenHighscore = false;
			asteroids.clear();
		}
		if (IsKeyDown(KEY_G) || player.Crash) { // end game when player crashes or if "G" is pressed - CJ
			gameOver = true;
		}
		if (!gameOver) {
			altitude = (-(int)player.pos.y + 730) / 10;
			player.update(); // Update player position and get user controls - DF
			camera.offset = { screenWidth / 2 - player.pos.x, screenHeight / 2 - player.pos.y }; // Move camera to center it on the player - CJ
																								 // for loop to update all asteroids in asteroids vector - CJ
																								 // later, check distance between each asteroid and rocket. distance between 2 points. - CJ
			// This ends the game if the rocket gets to close to the asteroid. - DF
			for (int i = 0; i < asteroids.size(); i++)
			{
				asteroids[i].update();

				if (distance(player.pos, asteroids[i].pos) < 50) {
					cout << "Game Over";
					gameOver = true;

				}
				// A loop that erases asteroids that are out of range - DF
				if (distance(player.pos, asteroids[i].pos) > 800 || asteroids[i].pos.y > 730) {
					asteroids.erase(asteroids.begin() + i);
				}

			}
			//adding asteroids to replace the one that were erased - DF
			if (asteroids.size() < 20 && player.pos.y < -300) {
				//top - DF
				float x = player.pos.x + (float)(rand() % 1400) - 700;
				float y = player.pos.y + (float)(rand() % 400) - 680;
				asteroids.push_back(asteroid({ x  ,y }, { (float)(rand() % 50 - 25), (float)(rand() % 50 - 25) }, asteroidTexture));
				//bottom - DF
				x = player.pos.x + (float)(rand() % 1400) - 700;
				y = player.pos.y + (float)(rand() % 400) + 240;
				asteroids.push_back(asteroid({ x  ,y }, { (float)(rand() % 50 - 25), (float)(rand() % 50 - 25) }, asteroidTexture));
				//right - DF
				x = player.pos.x + (float)(rand() % 400) + 400;
				y = player.pos.y + (float)(rand() % 600) - 300;
				asteroids.push_back(asteroid({ x  ,y }, { (float)(rand() % 50 - 25), (float)(rand() % 50 - 25) }, asteroidTexture));
				//left - DF
				x = player.pos.x + (float)(rand() % 400) - 800;
				y = player.pos.y + (float)(rand() % 600) - 540;
				asteroids.push_back(asteroid({ x  ,y }, { (float)(rand() % 50 - 25), (float)(rand() % 50 - 25) }, asteroidTexture));

			}

		}
		



		// draw section - CJ
		BeginDrawing();
		Begin2dMode(camera); // In game stuff is in this section. Position is relative to background or window
			ClearBackground(BLACK); //clear screen, make background black
			
			//set y offset t - NK
			int yoff = 0;
			if (player.pos.y < 0)
			{
				yoff = -480;
			}

			//set x offset t - NK
			int xoff = 0;
			if (player.pos.x < 0)
			{
				xoff = -852;
			}

			//Draw Space Background t - NK
			DrawTexture(Space, (int)(player.pos.x) / 852 * 852 + xoff, (int)(player.pos.y) / 480 * 480 + yoff, WHITE); // Centure t - NK
			DrawTexture(Space, (int)(player.pos.x) / 852 * 852 + xoff, (int)(player.pos.y) / 480 * 480 + 480 + yoff, WHITE); // Bottom t - NK
			DrawTexture(Space, (int)(player.pos.x) / 852 * 852 + xoff, (int)(player.pos.y) / 480 * 480 - 480 + yoff, WHITE); // Top t - NK
			DrawTexture(Space, (int)(player.pos.x) / 852 * 852 + 852 + xoff, (int)(player.pos.y) / 480 * 480 + yoff, WHITE); // Right t - NK
			DrawTexture(Space, (int)(player.pos.x) / 852 * 852 - 852 + xoff, (int)(player.pos.y) / 480 * 480 + yoff, WHITE); // Left t - NK
			DrawTexture(Space, (int)(player.pos.x) / 852 * 852 + 852 + xoff, (int)(player.pos.y) / 480 * 480 + 480 + yoff, WHITE); // Bottom Right t - NK
			DrawTexture(Space, (int)(player.pos.x) / 852 * 852 + 852 + xoff, (int)(player.pos.y) / 480 * 480 - 480 + yoff, WHITE); // Top Right t - NK
			DrawTexture(Space, (int)(player.pos.x) / 852 * 852 - 852 + xoff, (int)(player.pos.y) / 480 * 480 + 480 + yoff, WHITE); // Bottom Left t - NK
			DrawTexture(Space, (int)(player.pos.x) / 852 * 852 - 852 + xoff, (int)(player.pos.y) / 480 * 480 - 480 + yoff, WHITE); // Top Left t - NK
			
			//set x offset for planet t - NK
			int xxoff = 0;
			if (player.pos.x < 0)
			{
				xxoff = -1920;
			}
			//draw loop for planet texture t - NK
			
			DrawTexture(Planet, (int)(player.pos.x) / 1920 * 1920 - 1920 + xxoff, 0, WHITE); // Bottom Left t - NK
			DrawTexture(Planet, (int)(player.pos.x) / 1920 * 1920 + xxoff, 0, WHITE); // Bottom t - NK
			DrawTexture(Planet, (int)(player.pos.x) / 1920 * 1920 + 1920 + xxoff, 0, WHITE); // Bottom Right t - NK

			for (int i = 0; i < asteroids.size(); i++)
			{
				asteroids[i].draw();
			}

			player.draw(); // Draw rocket - CJ

		End2dMode();
			// Menu stuff here. Coordinates are relative to top left corner of window - CJ
			DrawText((string("Altitude: ") + to_string(altitude)).c_str(), 5, 5, 20, Color{ 255,255,255,255 });
			DrawText((string("Highscore: ") + to_string(highscore)).c_str(), 5, 25, 20, Color{ 255,255,255,255 });
			DrawText("Press r to reset", 5, 45, 20, Color{ 255,255,255,255 });
			if (gameOver) {
				DrawText("Game Over.", 240, 200, 60, RED);
				if (altitude > highscore) {
					DrawText("Set New Highscore!", 250, 270, 30, RED);
					if (!haveWrittenHighscore) {
						setHighScore(altitude);
						haveWrittenHighscore = true;
					}
				}
			}
		EndDrawing();
	}
	 
	return 0;
}