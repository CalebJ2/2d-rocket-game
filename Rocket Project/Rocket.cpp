#include "Rocket.h"
#include <raymath.h>
#include <raylib.h>
#include "Vector2Funcs.h"
#include <iostream>
#include <math.h>
#include <cmath>

// Update the rockets position - CJ
void Rocket::update() {
	// Controls - CJ
	if (IsKeyDown(KEY_RIGHT)) {
		torque = -2000.0f * (texture.height / 2 / 100);
		gimbalRot = 30 * DEG2RAD;
	}
	else if (IsKeyDown(KEY_LEFT)) {
		torque = 2000.0f * (texture.height / 2 / 100);
		gimbalRot = -30 * DEG2RAD;
	}
	else {
		gimbalRot = 0;
	}
	if (IsKeyDown(KEY_UP)) {
		throttle = 1.0f;
	}
	else {
		throttle = 0.0f;
	}
	if (IsKeyDown(KEY_A)) {
		acc.x = -cosf(orientation - 90 * DEG2RAD) * 3000 / mass; // realistic would be more like 1760n - CJ
		acc.y = sinf(orientation - 90 * DEG2RAD) * 3000 / mass;
	}
	else if (IsKeyDown(KEY_D)) {
		acc.x += -cosf(orientation + 90 * DEG2RAD) * 3000 / mass;
		acc.y += sinf(orientation + 90 * DEG2RAD) * 3000 / mass;
	}
	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
		acc.x += -cosf(orientation) * 3000 / mass;
		acc.y += sinf(orientation) * 3000 / mass;
	} 
	else if (IsKeyDown(KEY_W)) {
		acc.x += cosf(orientation) * 3000 / mass;
		acc.y += -sinf(orientation) * 3000 / mass;
	}
	acc.x += cosf(orientation) * cosf(gimbalRot) * maxThrot * throttle / mass; // force / mass = acc - CJ
	acc.y += -sinf(orientation) * cosf(gimbalRot) * maxThrot * throttle / mass;

	torque += -sinf(gimbalRot)*throttle*maxThrot * (texture.height / 2 / 100);

	acc.x -= vel.x*abs(vel.x)*0.001f; // drag for simulating atmosphere. Add acceleration in opposite direction of velocity. vel^2 * coefficient of drag (made up) - CJ
	acc.y -= vel.y*abs(vel.y)*0.001f;

	//Add gravity to acc.y here - CJ
	if (pos.y > -300)
	{
		acc.y += 1.2f; // moon gravity - CJ
	}

	float t = 1 / GetFPS(); // time since last update in seconds - CJ
	vel = v2Add(vel, v2Scale(acc, t)); // vel + acc * t - CJ
	if (pos.y > 730) // checks if rocket is on the ground - NK
	{
			if ((int)(vel.y) > 2 || abs((int)(vel.x)) > 2 || (int) (orientation * RAD2DEG) % 360 > 180 || ((int)(orientation * RAD2DEG) % 360 < 0 && (int)(orientation * RAD2DEG) % 360 > -180)) // checks rocket speed vertically and horizontally
			{
				Crash = true; // triggers Crash to be true to end the game
			}
			if (vel.y > 0) // checks if rocket is moving downwards - NK
		{
			vel.y = 0; // makes rocket stop moving - NK

		}
		vel.x = 0; // stops rocket from moving side-to-side - NK
		rotSpeed = 0; // stops rocket from rotating - NK
		
	}

	pos = v2Add(pos, v2Scale(v2Scale(vel, t), 100.0f)); // pos + vel * t - CJ

	rotSpeed += torque / momentOfInertia * t; // Add change in rotation speed to rotation speed - CJ
	orientation += rotSpeed * t;
	
	//unrelated to physics. Reset accelerations - CJ
	torque = 0.0f;
	acc.x = 0.0f;
	acc.y = 0.0f;
}

// Draw rocket, engine, and flame - CJ
void Rocket::draw() {

	// Calculate position of engine gimbal pivot point - CJ
	Vector2 rPos2;
	float centerRot = orientation - atan((0.5f*texture.height*scale) / (0.5f*texture.width*scale)); // get orientation of line going to center of texture to gimbal point in radians - CJ
	float centerHyp = sqrt(pow(texture.height / 2, 2) + pow(texture.width / 2, 2))*scale; // calculate distance from texture corner to center in pixels - CJ
	rPos2.x = pos.x - sinf(centerRot) * centerHyp;
	rPos2.y = pos.y - cosf(centerRot) * centerHyp;

	// Calculate position to actually draw engine so it rotates around gimbal point - CJ
	Vector2 ePos;
	
	float gimbalCenterRot = orientation - atan(((texture.height-100)*scale) / (0.5f*texture.width*scale)); // get orientation of line from rocket origin going to gimbal point of texture in radians - CJ
	float gimbalCenterHyp = sqrt(pow((texture.height-100)*scale, 2) + pow(texture.width / 2 * scale, 2)); // calculate distance from texture corner to center in pixels - CJ
	ePos.x = rPos2.x + sinf(gimbalCenterRot) * gimbalCenterHyp;
	ePos.y = rPos2.y + cosf(gimbalCenterRot) * gimbalCenterHyp;

	// Make rectangles for the drawing the rocket. - CJ
	Rectangle rSrcRect = { 0,0,texture.width,texture.height }; // The part of the texture to use - CJ
	Rectangle rDestRect = { pos.x,pos.y,texture.width*scale,texture.height*scale }; // The part of the screen to draw to - CJ
	Vector2 rOrigin = { texture.width*scale/2,texture.height*scale/2 }; // The point on the texture to rotate around - CJ

	// Rectangles for drawing the engine and flame. See above - CJ
	Rectangle eSrcRect = { 0,0,engineTex.width,engineTex.height };
	Rectangle eDestRect = { ePos.x,ePos.y,engineTex.width*scale,engineTex.height*scale };
	Vector2 eOrigin = { engineTex.width*scale/2, 0 };

	// Draw the rocket. - CJ
	// orientation - 90 to make 0 right like unit circle instead of up - CJ
	if (throttle > 0.0f) // Draw the flame if the throttle is on - CJ
		DrawTexturePro(flameTex, eSrcRect, eDestRect, eOrigin, orientation*RAD2DEG - 90 + gimbalRot*RAD2DEG, WHITE);
	DrawTexturePro(engineTex, eSrcRect, eDestRect, eOrigin, orientation*RAD2DEG - 90 + gimbalRot*RAD2DEG, WHITE); // Draw the engine - CJ
	DrawTexturePro(texture, rSrcRect, rDestRect, rOrigin, orientation*RAD2DEG - 90, WHITE); // Draw the rocket - CJ
}

// Reset rocket speed etc. - CJ
void Rocket::reset() {
	pos = { 400,730 };
	vel = { 0,0 };
	acc = { 0,0 };
	rotSpeed = 0.0f;
	orientation = 90.0f*DEG2RAD;
	Crash = false;
}

// Constructor that calls Object constructor and initializes rocket class - CJ
Rocket::Rocket(Vector2 position, Vector2 velocity, Texture2D Texture, Texture2D engineTexture, Texture2D flameTexture, float Mass) : Object(position, velocity, Texture) {
	engineTex = engineTexture;
	flameTex = flameTexture;
	gimbalRot = 0;
	mass = Mass;
	maxThrot = 45000;
	momentOfInertia = 2 * mass *pow((texture.height-150)/ 100 / 2, 2);
	orientation = 90.0f*DEG2RAD;
	Crash = false;
};