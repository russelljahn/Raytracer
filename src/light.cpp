/* Contains definitions of properties and functions for lights in the scene. */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "common.h"
#include "light.h"


/* Default constructor. The light is given a falloff of 0.25, and a position in space of (0.0, 0.0, 0.0). 
   Material is given default values. */
PointLight::PointLight(void) {
    this->intensity = 1.0;

    this->position[0] = 0.0;
    this->position[1] = 0.0;
    this->position[2] = 0.0;
    this->position[3] = 1.0;

    this->material.color.r = 1.0;
    this->material.color.g = 1.0;
    this->material.color.b = 1.0;
    this->material.color.a = 1.0;
    this->material.ambient = 1.0;
    this->material.specular = 1.0;
    this->material.diffuse = 1.0;
    this->material.shininess = 1.0;
    this->material.refraction = 1.0;

    this->falloff = .0075;
};


/* Constructor.  The light is given a falloff of FALLOFF and its position in space is
   set to (X, Y, Z). Material is given default values. */
PointLight::PointLight(double intensity, double falloff, double x, double y, double z) {
    this->intensity = intensity;

    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
    this->position[3] = 1.0;

    this->material.color.r = 1.0;
    this->material.color.g = 1.0;
    this->material.color.b = 1.0;
    this->material.color.a = 1.0;
    this->material.ambient = 1.0;
    this->material.specular = 1.0;
    this->material.diffuse = 1.0;
    this->material.shininess = 1.0;
    this->material.refraction = 1.0;

    this->falloff = falloff;
}


/* Constructor.  The light is given a falloff of FALLOFF and its position in space is
   set to (X, Y, Z). Material is set to MATERIAL. */
PointLight::PointLight(double intensity, double falloff, double x, double y, double z, Material material) {
    this->intensity = intensity;

    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
    this->position[3] = 1.0;

    this->material = material;

    this->falloff = falloff;
}


/* Returns the color of the light at POINT. */
Color PointLight::getColor(const Vector &point) const {
    double distance = (point - this->position).magnitude();

    /* intensity/attenuation */
    double finalIntensity = intensity/(falloff + falloff*distance + falloff*distance*distance);
    return finalIntensity * material.color;
}


/* Returns the intensity of the light at POINT. */
double PointLight::getIntensity(const Vector &point) const {
    double distance = (point - this->position).magnitude();

    /* intensity/attenuation */
    return intensity/(falloff + falloff*distance + falloff*distance*distance);
}


/* Takes a point and a direction from that point, and calculates whether the ray defined by them intersects 
     this light. If it does, returns true and modifies RETURN_INTERSECTION_POINT with the point of intersection. 
     Otherwise, returns false. */
bool PointLight::checkIntersection(const Vector &point, const Vector &direction, Vector &returnIntersectionPoint) const {

    /* Angle between the ray's direction vector and the vector from the ray's origin to the light position. */
    double angle = direction.dotProduct((this->position - point).normalize());

    /* If this angle is close to 1.0, then the vectors point the same way and the ray is considered to hit the light source. */
    if (angle >= 0.999 && angle <= 1.001) {
        returnIntersectionPoint = this->position;
        return true;
    }
    
    return false;
}


/* Print member function. */
void PointLight::print (ostream *os) const {
    printf("[PointLight with intensity: %.3f, falloff: %.3f, and color: (%.3f, %.3f, %.3f, %.3f) at (%5.3f, %5.3f, %5.3f)]", 
        intensity, falloff, material.color.r, material.color.g, material.color.b, material.color.a, 
        position.getEntry(0), position.getEntry(1), position.getEntry(2));
}


