/* Contains definitions for functions that draw to the computer's screen.

	Provided by Chandrajit Bajaj.
*/
	
#ifndef _LOWLEVEL_H_
#define _LOWLEVEL_H_

/* lowlevel drawing funtions */
void initCanvas(int, int);
void drawPixel(int, int, GLfloat, GLfloat, GLfloat);
void flushCanvas(void);

#endif	/* _LOWLEVEL_H_ */
