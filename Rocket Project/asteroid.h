#pragma once
#include <raylib.h>
#include "Object.h"
class asteroid : public Object {

public: 
	// used tr draw the asteroid. - DF
	float scale; 
	// updates asteroids position every frame 
	void update();
	// Draws the asteroid texture - DF
	void draw();
	// asteroid constuctor - DF
	asteroid(Vector2 position, Vector2 velocity, Texture2D Texture);

};
