#include "Vector2.h"


Vector2::Vector2()
{
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(Vector2& other)
{
	x = other.x;
	y = other.y;
}

Vector2::Vector2(Vector2&& other)
{
	x = other.x;
	y = other.y;
}

Vector2& Vector2::operator=(Vector2& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

float Vector2::Length()
{
	return sqrtf(pow(x, 2) + pow(y, 2));
}

Vector2 Vector2::Normalized()
{
	float length = Length();
	return Vector2(x / length, y / length);
}