/* Contains declarations for miscellaneous functions and globals. */

#ifndef MISC
#define MISC

#include "matrix.h"


	/* 
	Definitions: 
	============
	*/

	#define PI 3.14159265358979323846264338327

	/* 
	Function Prototypes: 
	====================
	*/

	/* Returns the greater of A or B. A is returned if they are equal. */
	double max(double a, double b);


	/* Returns the lesser of A or B. A is returned if they are equal. */
	double min(double a, double b);


	/* Returns the log base BASE of argument. */
	double log (double base, double argument);


	/* Takes two doubles and produces a random double value between them. Assumes MAXIMUM > MINIMUM. */
	double randomDouble (double minimum, double maximum);


	/* Takes a 4D matrix M in row-major order, and loads the 4D matrix which
	   does the same trasformation into the OpenGL MODELVIEW matrix, in
	   column-major order. */
	void load4DMatrix (const Matrix &m);


#endif

	