#ifndef VECTOR_2_H
#define VECTOR_2_H

struct Vector2
{
public:
	float x;
	float y;
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2 operator-() const;
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
};

#endif // !VECTOR_2_H