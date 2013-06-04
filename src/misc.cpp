/* Contains definitions for miscellaneous functions and globals. */


#include <cstdlib>
#include <cmath>

#include "common.h"
#include "misc.h"
#include "vector.h"
#include "matrix.h"



/* Returns the greater of A or B. A is returned if they are equal. */
double max(double a, double b) {
	return (b > a) ? b : a;
}



/* Returns the lesser of A or B. A is returned if they are equal. */
double min(double a, double b) {
	return (a > b) ? b : a;
}



/* Returns the log base BASE of argument. */
double log (double base, double argument) {
    /* log_base_B (x) = log_base_A (x) / log_base_A (B) */
    return log(argument)/log(base);
    
}



/* Takes two doubles and produces a random double value between them. Assumes MAXIMUM > MINIMUM. */
double randomDouble (double minimum, double maximum) {

	/* Generate a random integer and get the ratio of it out of all possible randomly generated integers. */
	double ratio = (double)rand() / RAND_MAX;

	/* Map the ratio to the range between MINIMUM and MAXIMUM, then add MINIMUM so that the result is between MINIMUM and MAXIMUM. */
	return minimum + ratio * (maximum - minimum);
}



/* Takes a 4D matrix M in row-major order, and loads the 4D matrix which
   does the same trasformation into the OpenGL MODELVIEW matrix, in
   column-major order. */
void load4DMatrix (const Matrix &m) {

	GLfloat newModelView [16];  /* three dimensional matrix */

	/* Take M and place it in the array column-by-column, aka in transpose order. */
	newModelView[0] =  m.getEntry(0, 0);   newModelView[1] =  m.getEntry(1, 0);   newModelView[2] =  m.getEntry(2, 0);   newModelView[3] =  m.getEntry(3, 0);
	newModelView[4] =  m.getEntry(0, 1);   newModelView[5] =  m.getEntry(1, 1);   newModelView[6] =  m.getEntry(2, 1);   newModelView[7] =  m.getEntry(3, 1);
	newModelView[8] =  m.getEntry(0, 2);   newModelView[9] =  m.getEntry(1, 2);   newModelView[10] = m.getEntry(2, 2);   newModelView[11] = m.getEntry(3, 2);
	newModelView[12] = m.getEntry(0, 3);   newModelView[13] = m.getEntry(1, 3);   newModelView[14] = m.getEntry(2, 3);   newModelView[15] = m.getEntry(3, 3);

	/* Set the current OpenGL matrix to the ModelView and load newModelView as the current ModelView matrix.*/
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(newModelView);
}
