/* Contains definitions for colors in the scene. */

#include <iostream>
#include <cstdio>

#include "color.h"

using namespace std;


/* Clamps each of the color's components so that they are in the inclusive range of [LOWER_BOUND, UPPER_BOUND]. 
   Modifies color and returns a reference to it. */
Color& clamp(Color &color, double lowerBound, double upperBound) {
	color.r = min(color.r, upperBound);
	color.g = min(color.g, upperBound);
	color.b = min(color.b, upperBound);

	color.r = max(color.r, lowerBound);
	color.g = max(color.g, lowerBound);
	color.b = max(color.b, lowerBound);

	return color;
}


/* Adds 2 colors together component-wise and returns a new color. */
Color operator+ (const Color &color1, const Color &color2) {
	Color newColor;

	newColor.r = color1.r + color2.r;
	newColor.g = color1.g + color2.g;
	newColor.b = color1.b + color2.b;
	newColor.a = color1.a + color2.a;

	return newColor;
}


/* Adds components of COLOR_2 to COLOR_1. Modifies COLOR_1 and returns a reference to it. */
Color& operator+= (Color &color1, const Color &color2) {
	color1.r += color2.r;
	color1.g += color2.g;
	color1.b += color2.b;
	color1.a += color2.a;

	return color1;
}


/* Subtracts COLOR_1 from COLOR_2 component-wise and returns a new color. */
Color operator- (const Color &color1, const Color &color2) {
	Color newColor;

	newColor.r = color1.r - color2.r;
	newColor.g = color1.g - color2.g;
	newColor.b = color1.b - color2.b;
	newColor.a = color1.a - color2.a;

	return newColor;
}


/* Subtracts components of COLOR_2 from COLOR_1. Modifies COLOR_1 and returns a reference to it. */
Color& operator-= (Color &color1, const Color &color2) {
	color1.r -= color2.r;
	color1.g -= color2.g;
	color1.b -= color2.b;
	color1.a -= color2.a;

	return color1;
}


/* Multiplies all of COLOR's components against VALUE and returns a new color. */
Color operator* (const Color &color, double value) {
	Color newColor;

	newColor.r = color.r * value;
	newColor.g = color.g * value;
	newColor.b = color.b * value;
	newColor.a = color.a * value;

	return newColor;
}


/* Multiplies all of COLOR's components against VALUE and returns a new color. */
Color operator* (double value, const Color &color) {
	Color newColor;

	newColor.r = color.r * value;
	newColor.g = color.g * value;
	newColor.b = color.b * value;
	newColor.a = color.a * value;

	return newColor;
}


/* Multiplies all of COLOR's components against VALUE. Modifies COLOR and returns a reference to it. */
Color& operator*= (Color &color, double value) {
	color.r *= value;
	color.g *= value;
	color.b *= value;
	color.a *= value;

	return color;
}


/* Divides all of COLOR's components against VALUE and returns a new color. */
Color operator/ (const Color &color, double value) {
	Color newColor;

	newColor.r = color.r / value;
	newColor.g = color.g / value;
	newColor.b = color.b / value;
	newColor.a = color.a / value;

	return newColor;
}


/* Divides all of COLOR's components against VALUE and returns a new color. */
Color operator/ (double value, const Color &color) {
	Color newColor;

	newColor.r = color.r / value;
	newColor.g = color.g / value;
	newColor.b = color.b / value;
	newColor.a = color.a / value;

	return newColor;
}


/* Divides all of COLOR's components against VALUE. Modifies COLOR and returns a reference to it. */
Color& operator/= (Color &color, double value) {
	color.r /= value;
	color.g /= value;
	color.b /= value;
	color.a /= value;

	return color;
}


/* Returns true if both COLOR_1 and COLOR_2 are equivalent. */
bool operator== (const Color &color1, const Color &color2) {
	return (color1.r == color2.r) &&
		   (color1.g == color2.g) &&
		   (color1.b == color2.b) &&
		   (color1.a == color2.a);
}


/* Printing operator. */
ostream& operator<< (ostream &os, const Color &color) {
	printf("[r:%8.5f, g:%8.5f, b:%8.5f, a:%8.5f]", color.r, color.g, color.b, color.a);
	return os;
}


