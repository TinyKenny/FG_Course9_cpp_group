#include "Matrix2x2.h"

void Matrix2x2::rotateByRadians(double angle)
{
	// TODO rotate
}

Vector2 Matrix2x2::transformVector(Vector2 inVector)
{
	return {
		m00 * inVector.x + m10 * inVector.y,
		m01 * inVector.x + m11 * inVector.y
	};
}
