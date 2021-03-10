#include "Vector2.h"

#include <math.h>

float Vector2::sqrDistance(const Vector2& lhs, const Vector2& rhs)
{
	float xPosDiff = lhs.x - rhs.x;
	float yPosDiff = lhs.y - rhs.y;
	return xPosDiff * xPosDiff + yPosDiff * yPosDiff;
}

float Vector2::magnitude() const
{
	return sqrtf(x * x + y * y);
}

void Vector2::setMagnitude(float desiredMagnitude)
{
	float magnitudeRatio = desiredMagnitude / magnitude();
	x *= magnitudeRatio;
	y *= magnitudeRatio;
}

/*
void Vector2::normalize()
{
	float mag = magnitude();
	x /= mag;
	y /= mag;
}
*/

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2 Vector2::operator-() const
{
	return { -x, -y };
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return { x + other.x, y + other.y };
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return { x - other.x, y - other.y };
}

Vector2 Vector2::operator*(const double& other) const
{
	return { x * (float)other, y * (float)other };
}








