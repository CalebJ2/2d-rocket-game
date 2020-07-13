#pragma once

#include <raylib.h>
class Object {
private:
	
public:
	Texture2D texture;
	Vector2 pos; // m
	Vector2 vel; // m/s
	Vector2 acc; // m/s^2
	float rotSpeed; // degrees/s
	float orientation; // degrees
	Object() {
		pos = { 0,0 };
		vel = { 0,0 };
		acc = { 0,0 };
		rotSpeed = 0.0f;
		orientation = 0.0f;
	}
	Object(Vector2 position, Vector2 velocity) {
		pos = position;
		vel = velocity;
		acc = { 0,0 };
		rotSpeed = 0.0f;
		orientation = 0.0f;
	};
	Object(Vector2 position, Vector2 velocity, Texture2D Texture) {
		pos = position;
		vel = velocity;
		acc = { 0,0 };
		rotSpeed = 0.0f;
		orientation = 0.0f;
		texture = Texture;
	};
};