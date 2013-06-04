/* Contains declarations of properties and functions for lights in the scene. */

#ifndef LIGHT
#define LIGHT

	#include "sceneobject.h"
	#include "material.h"
	#include "geometry.h"
	#include "vector.h" /* My own implementation of a 4x1 vector. */
	#include "color.h"
	

	/* A point light. */
	class PointLight : public SceneObject {
		public: 
			/* Member functions are defined in light.cpp. */

			/* Attenuation factor of the light; how quick the light fades. */
			double falloff;

			/* Intensity multiplier for the PointLight. */
			double intensity;

			/* Default constructor. The light is given an intensity of 0.75, attenuation of 0.25, and a position in space of (0.0, 0.0, 0.0). 
			   Material is given default values. */
			PointLight(void);

			/* Constructor.  The light is given an intensity of INTENSITY, attenuation of ATTENUATION, and its position in space is
			   set to (X, Y, Z). Material is given default values. */
			PointLight(double intensity, double falloff, double x, double y, double z);

			/* Constructor.  The light is given an INTENSITY, attenuation of ATTENUATION, and its position in space is
			   set to (X, Y, Z). Material is set to MATERIAL. */
			PointLight(double intensity, double falloff, double x, double y, double z, Material material);


			/* Returns the color of the light at POINT. */
			Color getColor(const Vector &point) const;

			/* Returns the intensity of the light at POINT. */
			double getIntensity(const Vector &point) const;


			/* Takes a point and a direction from that point, and calculates whether the ray defined by them intersects 
	  		   this sphere. If it does, returns true and modifies RETURN_INTERSECTION_POINT with the point of intersection. 
	   		   Otherwise, returns false. */
			bool checkIntersection(const Vector &point, const Vector &direction, Vector &returnIntersectionPoint) const;


			/* Print member function. */
			void print (ostream *os) const;
	};


#endif