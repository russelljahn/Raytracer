/* Contains declarations for colors in the scene. */

#ifndef COLOR
#define COLOR

	#include <iostream>

	using namespace std;


	/* Defines a color with red, green, blue, and alpha component values. */
	struct Color {
	  /* Amount of red, green, blue, and alpha components. These should be between 0.0 and 1.0. */
	  double r;
	  double g;
	  double b; 
	  double a;
	};
	

	/* Clamps each of the color's components so that they are in the inclusive range of [LOWER_BOUND, UPPER_BOUND]. 
	   Modifies color and returns a reference to it. */
	Color& clamp(Color &color, double lowerBound, double upperBound);


	/* Adds 2 colors together component-wise and returns a new color. */
	Color operator+ (const Color &color1, const Color &color2);

	/* Adds components of COLOR_2 to COLOR_1. Modifies COLOR_1 and returns a reference to it. */
	Color& operator+= (Color &color1, const Color &color2);



	/* Subtracts COLOR_1 from COLOR_2 component-wise and returns a new color. */
	Color operator- (const Color &color1, const Color &color2);

	/* Subtracts components of COLOR_2 from COLOR_1. Modifies COLOR_1 and returns a reference to it. */
	Color& operator-= (Color &color1, const Color &color2);



	/* Multiplies all of COLOR's components against VALUE and returns a new color. */
	Color operator* (const Color &color, double value);

	/* Multiplies all of COLOR's components against VALUE and returns a new color. */
	Color operator* (double value, const Color &color);

	/* Multiplies all of COLOR's components against VALUE. Modifies COLOR and returns a reference to it. */
	Color& operator*= (Color &color, double value);



	/* Divides all of COLOR's components against VALUE and returns a new color. */
	Color operator/ (const Color &color, double value);

	/* Divides all of COLOR's components against VALUE and returns a new color. */
	Color operator/ (double value, const Color &color);

	/* Divides all of COLOR's components against VALUE. Modifies COLOR and returns a reference to it. */
	Color& operator/= (Color &color, double value);


	/* Returns true if both COLOR_1 and COLOR_2 are equivalent. */
	bool operator== (const Color &color1, const Color &color2);



	/* Printing operator. */
	ostream& operator<< (ostream &os, const Color &color);


#endif