/* Contains definitions for vector and matrix transformation functions. */

#include "transform.h"
#include <cmath>



/* 

Vector Functions:
=================

These functions assume you provide a homogeneous vector V, aka a vector by the form:

[  x component  ]
[  y component  ]
[  z component  ]
[     1 or 0    ]  // 1 if a vector, 0 if a point.

*/


/* Translates V by (XTRANSLATE, YTRANSLATE, ZTRANSLATE). */
Vector translate (const Vector &v, double xTranslate, double yTranslate, double zTranslate) {

	/* Build translation matrix, multiply it by V to obtain the result, and return the result. */	
	return Matrix(1, 0, 0, xTranslate,
				  0, 1, 0, yTranslate,
				  0, 0, 1, zTranslate,
				  0, 0, 0, 1         ) * v;
}



/* Scales each of V's components by XSCALE, YSCALE, and ZSCALE. */
Vector scale (const Vector &v, double xScale, double yScale, double zScale) {

	/* Build scaling matrix, multiply it by V to obtain the result, and return the result. */
	return Matrix(xScale, 0,      0,      0,
				  0,      yScale, 0,      0,
				  0,      0,      zScale, 0,
				  0,      0,      0,      1) * v;

}



/* Rotates V by THETA radians along AXIS. Uses quaternions. */
Vector rotate (const Vector &v, Vector axis, double theta) {

	/* Obtain components of unit quaternion corresponding to the rotation to do. */
	double w = cos(theta/2.0);
	double x = sin(theta/2.0) * axis.getEntry(0);
	double y = sin(theta/2.0) * axis.getEntry(1);
	double z = sin(theta/2.0) * axis.getEntry(2);

	/* Build rotation matrix, multiply it by V to obtain the result, and return the result. */
	return Matrix(1 - 2*y*y - 2*z*z,      2*x*y - 2*w*z,        2*x*z + 2*w*y,      0.0,
				  2*x*y + 2*w*z,          1 - 2*x*x - 2*z*z,    2*y*z - 2*w*x,      0.0,
				  2*x*z - 2*w*y,          2*y*z + 2*w*x,        1 - 2*x*x - 2*y*y,  0.0,
				  0.0,                    0.0,                  0.0,                1.0) * v;

}



/* 

Matrix Functions:
=================

These functions assume you provide a position matrix, aka a matrix by the form:

[  x position, 0,          0,          0  ]
[  0,          y position, 0,          0  ]
[  0,          0,          z position, 0  ]
[  0,          0,          0,          1  ]

*/


/* Translates M by (XTRANSLATE, YTRANSLATE, ZTRANSLATE). */
Matrix translate (const Matrix &m, double xTranslate, double yTranslate, double zTranslate) {

	/* Add m to a new matrix containing corresponding entries with the amounts to translate and return the result. */
	return m * Matrix(1, 0, 0, xTranslate,	
					  0, 1, 0, yTranslate,
					  0, 0, 1, zTranslate,
					  0, 0, 0, 1         );

}



/* Scales each of M's components by XSCALE, YSCALE, and ZSCALE. */
Matrix scale (const Matrix &m, double xScale, double yScale, double zScale) {

	/* Build scaling matrix, multiply it by M to obtain the result, and return the result. */
	return m * Matrix(xScale, 0,      0,      0,
					  0,      yScale, 0,      0,
					  0,      0,      zScale, 0,
					  0,      0,      0,      1);

}



/* Rotates M by THETA radians along AXIS. Uses quaternions. */
Matrix rotate (const Matrix &m, Vector axis, double theta) {

	/* Obtain components of unit quaternion corresponding to the rotation to do. */
	double w = cos(theta/2.0);
	double x = sin(theta/2.0) * axis.getEntry(0);
	double y = sin(theta/2.0) * axis.getEntry(1);
	double z = sin(theta/2.0) * axis.getEntry(2);

	/* Build rotation matrix, multiply it by M to obtain the result, and return the result. */
	return m * Matrix(1 - 2*y*y - 2*z*z,      2*x*y - 2*w*z,        2*x*z + 2*w*y,      0.0,
					  2*x*y + 2*w*z,          1 - 2*x*x - 2*z*z,    2*y*z - 2*w*x,      0.0,
				  	  2*x*z - 2*w*y,          2*y*z + 2*w*x,        1 - 2*x*x - 2*y*y,  0.0,
				  	  0.0,                    0.0,                  0.0,                1.0);

}


