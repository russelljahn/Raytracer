/* Contains definitions for predefined objects that can be used in the scene, such as spheres and triangles. */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "geometry.h"
#include "common.h"
#include "raytrace.h"
#include "transform.h"
#include "vector.h" /* My own implementation of a 4x1 vector. */
#include "color.h"
#include "material.h"

/* 
----------------------
    Sphere methods. 
---------------------- 
*/


/* Defualt constructor. The sphere is given a radius of 1.0 and a position in space of (0.0, 0.0, 0.0). */
Sphere::Sphere(void) {
    this->radius = 1.0;

    this->position[0] = 0.0;
    this->position[1] = 0.0;
    this->position[2] = 0.0;
    this->position[3] = 1.0;

    this->material.color.r = 0.75;
    this->material.color.g = 0.75;
    this->material.color.b = 0.75;
    this->material.color.a = 1.0;
    this->material.ambient = 1.0;
    this->material.specular = 1.0;
    this->material.diffuse = 1.0;
    this->material.shininess = 75.0;
    this->material.refraction = 1.0;
}



/* Constructor. The sphere is given a radius of RADIUS and its position in space is
   set to (X, Y, Z). */
Sphere::Sphere(double radius, double x, double y, double z) {
    this->radius = radius;

    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
    this->position[3] = 1.0;

    this->material.color.r = 0.75;
    this->material.color.g = 0.75;
    this->material.color.b = 0.75;
    this->material.color.a = 1.0;
    this->material.ambient = 1.0;
    this->material.specular = 1.0;
    this->material.diffuse = 1.0;
    this->material.shininess = 75.0;
    this->material.refraction = 1.0;
}



/* Constructor. The sphere is given a radius of RADIUS and its position in space is
   set to (X, Y, Z). Material is set to MATERIAL. */
Sphere::Sphere(double radius, double x, double y, double z, Material material) {
    this->radius = radius;

    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
    this->position[3] = 1.0;

    this->material = material;
}



/* Takes a point and a direction from that point, and calculates whether the ray defined by them intersects 
   this sphere. If it does, returns true and modifies RETURN_INTERSECTION_POINT with the point of intersection. 
   Otherwise, returns false. */
bool Sphere::checkIntersection(const Vector &point, const Vector &direction, Vector &returnIntersectionPoint) const {

    /* The following code takes the parametric form of the ray defined by POINT and DIRECTION, plugs it into
       the equation of a sphere, and attempts to solve for t to find out where the ray intersects the sphere 
       (if at all). */

    /* Coefficients of the quadratic formula. */
    double a, b, c;

    /* Transform POINT into the sphere's object coordinates. (Note: This sphere is at (0, 0, 0) in 
       its own coordinate space.) */
    Vector s = point - position;

    /* Derive coefficients of the quadratic formula relating the ray to the sphere. */
    a = direction.dotProduct(direction);
    b = 2 * (s.dotProduct(direction));
    c = s.dotProduct(s) - (radius * radius);

    /* Discriminant of the quadratic formula. We can use this to determine how many roots the quadratic formula has. */
    double discriminant = b*b - 4*a*c;

    /* If discriminant is less than 0, then there are no real roots, and thus there is no intersection. */
    if (discriminant < 0) {
        return false;
    }
   
   /* Solves for the value of t corresponding to the closest intersection point of the ray & sphere to the origin of the ray. */
   double t = (-b - sqrt(discriminant)) / (2*a);

    /* If t is negative, then the intersection is behind the ray. */
    if (t < 0) {
        return false;
    }

    /* Calculate the intersection point of the ray and the sphere. */
    returnIntersectionPoint[0] = point.getEntry(0) + t*direction.getEntry(0);
    returnIntersectionPoint[1] = point.getEntry(1) + t*direction.getEntry(1);
    returnIntersectionPoint[2] = point.getEntry(2) + t*direction.getEntry(2);

    return true;

}


/* Sphere print member function. */
void Sphere::print (ostream *os) const {
    printf("[Sphere with radius %.3f at (%5.3f, %5.3f, %5.3f)]", radius, position.getEntry(0), position.getEntry(1), position.getEntry(2));
}





/* 
----------------------
    Plane methods. 
---------------------- 
*/


/* Default constructor. The plane is a normal of (0.0, 1.0, 0.0) and given a position in space of (0.0, 0.0, 0.0). 
   Material is given default values. */
Plane::Plane (void) {

    this->normal = Vector (0.0, 1.0, 0.0, 0.0);

    this->position[0] = 0.0;
    this->position[1] = 0.0;
    this->position[2] = 0.0;
    this->position[3] = 1.0;

    this->material.color.r = 0.75;
    this->material.color.g = 0.75;
    this->material.color.b = 0.75;
    this->material.color.a = 1.0;
    this->material.ambient = 1.0;
    this->material.specular = 1.0;
    this->material.diffuse = 1.0;
    this->material.shininess = 75.0;
    this->material.refraction = 1.0;

}   



/* Constructor. The plane's normal is set to NORMAL and position in space is set to (X, Y, Z). Material is given default values. 
   Normal will be converted into a unit vector. */
Plane::Plane (const Vector &normal, double x, double y, double z) {

    this->normal = normal;
    this->normal.normalize();

    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
    this->position[3] = 1.0;

    this->material.color.r = 0.75;
    this->material.color.g = 0.75;
    this->material.color.b = 0.75;
    this->material.color.a = 1.0;
    this->material.ambient = 1.0;
    this->material.specular = 1.0;
    this->material.diffuse = 1.0;
    this->material.shininess = 75.0;
    this->material.refraction = 1.0;

}



/* Constructor. The plane's normal is set to NORMAL and position in space is set to (X, Y, Z). Material is set to MATERIAL. 
   Normal will be converted into a unit vector. */
Plane::Plane (const Vector &normal, double x, double y, double z, Material material) {
    
    this->normal = normal;
    this->normal.normalize();

    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
    this->position[3] = 1.0;

    this->material = material;

}



/* Returns the color of the plane at POINT. */
Color Plane::getColor(const Vector &point) const {
    cout << "In Plane::getColor()!!!!" << endl;
    Color returnColor = {0.0, 1.0, 0.0, this->material.color.a};
    return returnColor;
    if (((int)point.getEntry(0)) % 100 <= 50) {
        returnColor.r = 1.0;
        returnColor.g = 1.0;
        returnColor.b = 1.0;
        return returnColor;
    } 
    else {
        return returnColor;
    }
}



/* Takes a point and a direction from that point, and calculates whether the ray defined by them intersects 
   this plane. If it does, returns true and modifies RETURN_INTERSECTION_POINT with the point of intersection. 
   Otherwise, returns false. */
bool Plane::checkIntersection(const Vector &point, const Vector &direction, Vector &returnIntersectionPoint) const {

    double angleBetweenNormalAndRay = normal.dotProduct(direction);

    /* If this angle is close to 0.0, then the ray travels parallel to the plane. We'll consider all parallel 
       rays as NOT intersecting the plane, including parallel rays that lay directly on the plane. */
    if (angleBetweenNormalAndRay <= 0.0001 && angleBetweenNormalAndRay >= -0.0001) {
        return false;
    }
    

    /* Solves for t where t is the intersection of the ray & the plane in the parametric equation of the ray. */
    double t = (position-point).dotProduct(normal)/angleBetweenNormalAndRay;

    /* If t is negative, then the intersection is behind the ray. */
    if (t < 0) {
        return false;
    }

    /* Calculate the intersection point of the ray and the plane based on t. */
    returnIntersectionPoint[0] = point.getEntry(0) + t*direction.getEntry(0);
    returnIntersectionPoint[1] = point.getEntry(1) + t*direction.getEntry(1);
    returnIntersectionPoint[2] = point.getEntry(2) + t*direction.getEntry(2);

    return true;
}



/* Print member function. */
void Plane::print (ostream *os) const {
    printf("[Plane at (%5.3f, %5.3f, %5.3f)]", position.getEntry(0), position.getEntry(1), position.getEntry(2));
}





/* 
----------------------
    Triangle methods. 
---------------------- 
*/


/*Default constructor. */
Triangle::Triangle (void) {

    this->position[0] = 0.0;
    this->position[1] = 0.0;
    this->position[2] = 0.0;
    this->position[3] = 1.0;

    this->vertex0 = Vector (-0.5, 1.0, 0.0, 1.0);
    this->vertex1 = Vector ( 0.0, 1.0, 0.0, 1.0);
    this->vertex2 = Vector ( 0.5, 0.0, 0.0, 1.0);



    this->material.color.r = 0.75;
    this->material.color.g = 0.75;
    this->material.color.b = 0.75;
    this->material.color.a = 1.0;
    this->material.ambient = 1.0;
    this->material.specular = 1.0;
    this->material.diffuse = 1.0;
    this->material.shininess = 75.0;
    this->material.refraction = 1.0;

}   


Vector Triangle::getNormal(const Vector &point) const {
    Vector e1 = (vertex1-vertex0);
    Vector e2 = (vertex2-vertex0);
    return e1.crossProduct(e2).normalize();
}


/* Takes a point and a direction from that point, and calculates whether the ray defined by them intersects 
   this triangle. If it does, returns true and modifies RETURN_INTERSECTION_POINT with the point of intersection. 
   Otherwise, returns false. */
bool Triangle::checkIntersection(const Vector &point, const Vector &direction, Vector &returnIntersectionPoint) const {
    Vector e1 = (vertex1-vertex0);
    Vector e2 = (vertex2-vertex0);
    Vector q = direction.crossProduct(e2);

    double a = e1.dotProduct(q);

    if (a > -0.0001 && a < 0.0001) {
        return false;
    }

    double f = 1.0/a;

    Vector s = point-vertex0;
    double u = f*(s.dotProduct(q));

    if (u < 0.0) {
        return false;
    }

    Vector r = s.crossProduct(e1);
    double v = f*(direction.dotProduct(r));

    if (v < 0.0 || u+v > 1.0) {
        return false;
    }

    /* Calculate intersection point using barycentric coordinates. */
    returnIntersectionPoint = (1-u-v)*vertex0 + u*vertex1 + v*vertex2;
    return true;
}


/* Print member function. */
void Triangle::print (ostream *os) const {
    printf("[Triangle at (%5.3f, %5.3f, %5.3f)}", position.getEntry(0), position.getEntry(1), position.getEntry(2));
}







