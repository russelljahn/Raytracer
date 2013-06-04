/* Contains the interface for an object in the scene. New objects can be created by implementing the virtual functions declared here. */

#ifndef SCENE_OBJECT
#define SCENE_OBJECT

	#include <vector> /* STL vector. */
	#include <list>
	#include "common.h"
	#include "vector.h" /* My own implementation of a 4x1 vector. */
	#include "material.h"

	using namespace std;


	/* Abstract class for an object in the scene. This could include primitives, polyhedra, or even lights. */
	class SceneObject {
		
		public:
			/* Position of the object in the scene. */
			Vector position;

			/* A SceneObject must have a material associated with it. */
			Material material;

			
			/* Default contructor. */
			SceneObject ();

			/* Takes a point and a direction from that point, and calculates whether the ray starting from that point along
			   its direction intersects this object. If it does, returns true and modifies RETURN_INTERSECTION_POINT with 
			   the point of intersection. Otherwise, returns false. */
			virtual bool checkIntersection(const Vector &point, const Vector &direction, Vector &returnIntersectionPoint) const;

			/* Returns a normal vector at POINT on the SceneObject. Assumes POINT does lay on the outside of the SceneObject. */
			virtual Vector getNormal(const Vector &point) const;

			/* Returns the color of the SceneObject at POINT. */
			virtual Color getColor(const Vector &point) const;

			/* Returns a reference to the x component of the SceneObject's position. */
			double& x (void); 

			/* Returns a reference to the y component of the SceneObject's position. */
			double& y (void); 

			/* Returns a reference to the z component of the SceneObject's position. */
			double& z (void); 

			/* Returns true if SCENE_OBJECT is equivalent to THIS, false otherwise. */
			virtual bool equals (const SceneObject &sceneObject) const;

			/* Print member function. */
			virtual void print (ostream *os) const;

			

	};


	/* Printing operator. */
	ostream& operator<< (ostream &os, const SceneObject &sceneObject);

	

#endif