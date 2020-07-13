#include "asteroid.h"
#include <raymath.h>
#include <raylib.h>
#include "Vector2Funcs.h"
#include <iostream>
#include <math.h>
#include <cmath>

void asteroid::update() {
	// adds gravity to asteroids so they will fall down to the earth within the gravatational pull of the moon. - DF
	if (pos.y > -300)
	{
		acc.y += 1.2f; // moon gravity
	}
	float t = 1 / GetFPS(); // time since last update in seconds
	vel = v2Add(vel, v2Scale(acc, t)); // vel + acc * t
	pos = v2Add(pos, v2Scale(vel, t)); // pos + vel * t

	//Sets the roratiaion speed of the asteroids. CJ 
	orientation += rotSpeed * t;
}
// This is a constructor for the asteroid class, calls the constructor for the object class. - DF
asteroid::asteroid(Vector2 position, Vector2 velocity, Texture2D Texture) :Object(position, velocity, Texture) {
	// How big the asteroids are
	scale = 0.2f;
}


// Draws the image of the asteriod. - DF
void asteroid::draw() {
	// A portion of the texture to use 
	Rectangle aSrcRect = { 0,0,texture.width,texture.height };
	// sets were to draw the rectangle texture on the screen 
	Rectangle aDestRect = { pos.x,pos.y,texture.width*scale,texture.height*scale };
	// Where to center the destination rectangle around. 
	Vector2 aOrigin = { texture.width*scale / 2, 0 }; 
	DrawTexturePro(texture, aSrcRect, aDestRect, aOrigin, orientation , WHITE);
	
	

}

