/* Contains declarations for predefined objects that can be used in the scene, such as spheres and triangles. */
	
#ifndef GEOMETRY
#define GEOMETRY


	#include "sceneobject.h"
	#include "material.h"


	/* A sphere. Member functions are defined in geometry.cpp. */
	class Sphere : public SceneObject {
	
		public:

			/* A sphere has a radius from its center point. */
			double radius;

			/* Default constructor. The sphere is given a radius of 1.0 and a position in space of (0.0, 0.0, 0.0). 
			   Material is given default values. */
			Sphere (void);

			/* Constructor. The sphere is given a radius of RADIUS and its position in space is
			   set to (X, Y, Z). Material is given default values. */
			Sphere (double radius, double x, double y, double z);

			/* Constructor. The sphere is given a radius of RADIUS and its position in space is
			   set to (X, Y, Z). Material is set to MATERIAL. */
			Sphere (double radius, double x, double y, double z, Material material);


			/* Takes a point and a direction from that point, and calculates whether the ray defined by them intersects 
	  		   this sphere. If it does, returns true and modifies RETURN_INTERSECTION_POINT with the point of intersection. 
	   		   Otherwise, returns false. */
			bool checkIntersection(const Vector &point, const Vector &direction, Vector &returnIntersectionPoint) const;


			/* Print member function. */
			void print (ostream *os) const;
	};





	/* An infinite plane. Member functions are defined in geometry.cpp. */
	class Plane : public SceneObject {
	
		public:

			/* A plane is defined by its position and a normal which defines its orientation. */
			Vector normal;

			/* Default constructor. The plane is given a position in space of (0.0, 0.0, 0.0). 
			   Material is given default values. */
			Plane (void);

			/* Constructor. The plane's normal is set to NORMAL and position in space is set to (X, Y, Z). Material is given default values. */
			Plane (const Vector &normal, double x, double y, double z);

			/* Constructor. The plane's normal is set to NORMAL and position in space is set to (X, Y, Z). Material is set to MATERIAL. */
			Plane (const Vector &normal, double x, double y, double z, Material material);

			/* Returns the color of the plane at POINT. */
			Color getColor(const Vector &point) const;

			/* Takes a point and a direction from that point, and calculates whether the ray defined by them intersects 
	  		   this plane. If it does, returns true and modifies RETURN_INTERSECTION_POINT with the point of intersection. 
	   		   Otherwise, returns false. */
			bool checkIntersection(const Vector &point, const Vector &direction, Vector &returnIntersectionPoint) const;


			/* Print member function. */
			void print (ostream *os) const;
	};




	/* A triangle. Member functions are defined in geometry.cpp. */
	class Triangle : public SceneObject {
	
		public:

			/* A triangle has 3 vertices. */
			Vector vertex0;
			Vector vertex1;
			Vector vertex2;

			/* Default constructor. */
			Triangle (void);

			/* Takes a point and a direction from that point, and calculates whether the ray defined by them intersects 
	  		   this triangle. If it does, returns true and modifies RETURN_INTERSECTION_POINT with the point of intersection. 
	   		   Otherwise, returns false. */
			bool checkIntersection(const Vector &point, const Vector &direction, Vector &returnIntersectionPoint) const;

			Vector getNormal(const Vector &point) const;

			/* Print member function. */
			void print (ostream *os) const;
	};




#endif
