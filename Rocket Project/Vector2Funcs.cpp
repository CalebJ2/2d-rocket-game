#include "Vector2Funcs.h"
#include <math.h>

Vector2 v2Sub(Vector2& v1, Vector2& v2) { // Subtract - CJ
	return{ v1.x - v2.x,v1.y - v2.y };
}
Vector2 v2Scale(Vector2& v, float scalar) { // Scale - CJ
	return{ v.x * scalar,v.y * scalar };
}
Vector2 v2Add(Vector2& v1, Vector2& v2) { // Add - CJ
	return{ v1.x + v2.x, v1.y + v2.y };
}
Vector2 v2Mult(Vector2& v1, Vector2& v2) { // Multiply - CJ
	return{ v1.x * v2.x, v1.y * v2.y };
}
Vector2 v2Div(Vector2& v1, float& divisor) { // Divide - CJ
	return{ v1.x / divisor, v1.y / divisor };
}
Vector2 makeV2(float x, float y) { // Like a constructor but not because adding a real one breaks raylib
	return{ x,y };
}
float v2Mag(Vector2 v) { // Magnitude of vector - CJ
	return pow(pow((double)v.x, 2) + pow((double)v.y, 2), 0.5); // sqrt(x^2+y^2)
}

float distance(Vector2& v1, Vector2& v2) {
	return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2)); // finds the distance between 2 vectors - DF
}