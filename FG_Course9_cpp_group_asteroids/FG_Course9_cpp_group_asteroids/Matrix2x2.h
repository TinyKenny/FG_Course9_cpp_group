#ifndef MATRIX_2X2_H
#define MATRIX_2X2_H

#include "Vector2.h"

/*
+---+---+
|m00|m10|
+---+---+
|m01|m11|
+---+---+

formula: (might be wrong, idk im not a mathematician)
+----------+-----------+
|cos(angle)|-sin(angle)|
+----------+-----------+
|sin(angle)| cos(angle)|
+----------+-----------+

identity matrix:
+---+---+
|1.0|0.0|
+---+---+
|0.0|1.0|
+---+---+
*/

struct Matrix2x2
{
public:
	void rotateByRadians(double angle);
	Vector2 transformVector(Vector2 inVector);
private:
	float m00 = 1.0f;
	float m10 = 0.0f;
	float m01 = 0.0f;
	float m11 = 1.0f;
};

/*
transformation matrix:

xWorld = m00 * xIn + m10 * yIn
yWorld = m01 * xIn + m11 * yIn

*/

#endif // !MATRIX_2X2_H