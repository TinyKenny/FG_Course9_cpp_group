#include "Matrix2x2.h"

#include <math.h>
#include <iostream>

void Matrix2x2::rotateByRadians(double angleRad)
{
	double angCos = cos(angleRad);
	double angSin = sin(angleRad);

	double m00Other = angCos;
	double m01Other = -angSin;
	double m10Other = angSin;
	double m11Other = angCos;

	double m00Rotated = m00 * m00Other + m01 * m10Other;
	double m01Rotated = m00 * m01Other + m01 * m11Other;
	double m10Rotated = m10 * m00Other + m11 * m10Other;
	double m11Rotated = m10 * m01Other + m11 * m11Other;
	
	m00 = m00Rotated;
	m01 = m01Rotated;
	m10 = m10Rotated;
	m11 = m11Rotated;
}

Vector2 Matrix2x2::transformVector(const Vector2 inVector)
{
	return {
		(float)m00 * inVector.x + (float)m01 * inVector.y,
		(float)m10 * inVector.x + (float)m11 * inVector.y
	};
}
