/* Contains definitions for a material, which SceneObjects are made out of. Materials are composed of colors and shading properties. */

#include <iostream>
#include <cstdio>

#include "material.h"

using namespace std;


/* Returns true if both MATERIAL_1 and MATERIAL_2 are equivalent. */
bool operator== (const Material &material1, const Material &material2) {
	return (material1.ambient    ==  material2.ambient)  &&
		   (material1.specular   ==  material2.specular) &&
		   (material1.diffuse    ==  material2.diffuse)  &&
		   (material1.shininess  ==  material2.shininess)  &&
		   (material1.refraction ==  material2.refraction)  &&
		   (material1.color      ==  material2.color);
}


/* Printing operator. */
ostream& operator<< (ostream &os, const Material &material) {
	printf("[ambient: %5.3f, specular %5.3f, diffuse: %5.3f, shininess: %5.3f, refraction: %5.3f]", 
		material.ambient, material.specular, material.diffuse, material.shininess, material.refraction);
	return os;
}


