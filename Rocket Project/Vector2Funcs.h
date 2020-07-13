#pragma once

#include <raylib.h>
#include <raymath.h>

// Some functions for working with Vector2. Raylib only has them for Vector3 - CJ

Vector2 v2Sub(Vector2& v1, Vector2& v2); // subtract - CJ
Vector2 v2Scale(Vector2& v, float scalar); // scale - CJ
Vector2 v2Add(Vector2& v1, Vector2& v2); // add - CJ
Vector2 v2Mult(Vector2& v1, Vector2& v2); // multiply - CJ
Vector2 v2Div(Vector2& v1, float& divisor); // divide - CJ
Vector2 makeV2(float x, float y); // Like a constructor. Adding an actual constructor to Vector2 breaks raylib - CJ
float distance(Vector2& v1, Vector2& v2); // Calculate distance between two vectors - DF
float v2Mag(Vector2 v); // Calculate length of vector - CJ