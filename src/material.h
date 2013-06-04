/* Contains declarations for a material, which SceneObjects are made out of. Materials are composed of colors and shading properties. */

#ifndef MATERIAL
#define MATERIAL

	#include <iostream>
	#include <cstdio>

	#include "color.h"

	using namespace std;


	/* Defines the material properties of an object in the scene. */
	struct Material {
		struct Color color;

		/* Components of the Phong Lighting Model. Should be between 0.0 and 1.0. */
		double ambient; 
		double specular;
		double diffuse;


		/* Should be between 0.0 and 500.0. Used with specular highlights; determines how mirror-like the surface is. */
		double shininess; 

		/* Should be between 0.0 and 3.0. The refraction index of the material; determines how light bends through the object.
		   A value of 1.0 gives no bending (like air). Refraction is only used if the object is translucent. */
		double refraction; 
	};


	/* Returns true if both MATERIAL_1 and MATERIAL_2 are equivalent. */
	bool operator== (const Material &material1, const Material &material2);


	/* Printing operator. */
	ostream& operator<< (ostream &os, const Material &material);


#endif