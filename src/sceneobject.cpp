/* Contains definitions for an object in the scene. */

#include <vector> /* STL vector. */
#include <cstdio>
#include <list>
#include <cmath>
#include "common.h"
#include "sceneobject.h"
#include "geometry.h"
#include "vector.h" /* My own implementation of a 4x1 vector. */
#include "color.h"
#include "material.h"
#include "misc.h"

using namespace std;


/* Default constructor. */
SceneObject::SceneObject () {
	position[3] = 1.0;

    this->material.color.r = 0.75;
    this->material.color.g = 0.75;
    this->material.color.b = 0.75;
    this->material.color.a = 1.0;
    this->material.ambient = 1.0;
    this->material.specular = 1.0;
    this->material.diffuse = 1.0;
    this->material.shininess = 75.0;
    this->material.shininess = 100.0;
    this->material.refraction = 1.0;
}

/* Takes a point and a direction from that point, and calculates whether the ray starting from that point along
   its direction intersects this object. If it does, returns true and modifies RETURN_INTERSECTION_POINT with 
   the point of intersection. Otherwise, returns false. */
bool SceneObject::checkIntersection(const Vector &point, const Vector &direction, Vector &returnIntersectionPoint) const {
	return false;
}

/* Returns a normal vector at POINT on the SceneObject. Assumes POINT does lay on the outside of the SceneObject. 
   Return vector may not be of unit length! */
Vector SceneObject::getNormal(const Vector &point) const {
	return (point-position);
}

/* Returns the color of the SceneObject at POINT. */
Color SceneObject::getColor(const Vector &point) const {
	return material.color;
}


/* Returns a reference to the x component of the SceneObject's position. */
double& SceneObject::x (void) {
	return position[0];
} 

/* Returns a reference to the y component of the SceneObject's position. */
double& SceneObject::y (void) {
	return position[1];
} 

/* Returns a reference to the z component of the SceneObject's position. */
double& SceneObject::z (void) {
	return position[2];
}

/* Returns true if SCENE_OBJECT is equivalent to THIS, false otherwise. */
bool SceneObject::equals (const SceneObject &sceneObject) const {
	return (this->material == sceneObject.material) && (this->position == sceneObject.position);
}

/* SceneObject print member function. */
void SceneObject::print (ostream *os) const {
	printf("[SceneObject at (%5.3f, %5.3f, %5.3f)]", position.getEntry(0), position.getEntry(1), position.getEntry(2));
}


/* SceneObject printing operator. */
ostream& operator<< (ostream &os, const SceneObject &sceneObject) {
	sceneObject.print(&os);
	return os;
}

