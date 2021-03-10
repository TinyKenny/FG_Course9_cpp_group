#ifndef VECTOR_2_H
#define VECTOR_2_H

struct Vector2
{
public:
	static float sqrDistance(const Vector2& lhs, const Vector2& rhs);
public:
	float x;
	float y;

	//float sqrMagnitude() const;
	float magnitude() const;
	void setMagnitude(float desiredMagnitude);
	//void normalize();

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2 operator-() const;
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const double& other) const;
};

#endif // !VECTOR_2_H