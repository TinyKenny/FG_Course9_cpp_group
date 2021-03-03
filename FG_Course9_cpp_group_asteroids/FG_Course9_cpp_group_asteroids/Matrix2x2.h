#ifndef MATRIX_2X2_H
#define MATRIX_2X2_H

#include "Vector2.h"

/*
+---+---+
|m00|m01|
+---+---+
|m10|m11|
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
	void rotateByRadians(double angleRad);
	Vector2 transformVector(const Vector2 inVector) const;
private:
	double m00 = 1.0f;
	double m01 = 0.0f;
	double m10 = 0.0f;
	double m11 = 1.0f;
};

/*
transformation matrix:

xWorld = m00 * xIn + m01 * yIn
yWorld = m10 * xIn + m11 * yIn

*/

#endif // !MATRIX_2X2_H