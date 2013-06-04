/* Contains interface for vector and matrix transformation functions. */

#ifndef TRANSFORM
#define TRANSFORM


	#include "vector.h"
	#include "matrix.h"



	/*

	Vector Functions:
	=================

	These functions assume you provide a homogeneous vector, aka a vector by the form:

	[  x component  ]
	[  y component  ]
	[  z component  ]
	[     1 or 0    ]

	*/


	/* Translates the vector by (XTRANSLATE, YTRANSLATE, ZTRANSLATE). */
	Vector translate (const Vector &v, double xTranslate, double yTranslate, double zTranslate);

	/* Scales each of the vector's components by XSCALE, YSCALE, and ZSCALE. */
	Vector scale (const Vector &v, double xScale, double yScale, double zScale);

	/* Rotates V by THETA radians along AXIS. Uses quaternions. */
	Vector rotate (const Vector &v, Vector axis, double theta);



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
	Matrix translate (Matrix m, double xTranslate, double yTranslate, double zTranslate);

	/* Scales each of M's components by XSCALE, YSCALE, and ZSCALE. */
	Matrix scale (Matrix m, double xScale, double yScale, double zScale); 

	/* Rotates M by THETA radians along AXIS. Uses quaternions. */
	Matrix rotate (Matrix m, Vector axis, double theta);


#endif

