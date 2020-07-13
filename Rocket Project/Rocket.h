#pragma once

#include "Object.h"

class Rocket : public Object {
private:
	Texture2D engineTex;
	Texture2D flameTex;
	float gimbalRot;
	float mass; // in kg - CJ
	float maxThrot; // in newtons - CJ
	float momentOfInertia; // 2mr^2 - CJ
public:
	float torque; // radians/s^2 - CJ
	float throttle; // from 0 to 1 - CJ
	float scale;
	void update();
	void draw();
	void destroy();
	void reset();
	bool Crash;
	Rocket(Vector2 position, Vector2 velocity, Texture2D Texture, Texture2D engineTexture, Texture2D flameTexture, float mass);
};