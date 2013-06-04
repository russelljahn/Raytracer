/* Contains declarations for functions and variables that handle the raytracing process. */
#ifndef _RAYTRACE_H_
#define _RAYTRACE_H_


#include <vector> /* STL vector. */
#include "vector.h" /* My own implementation of a 4x1 vector. */
#include "color.h"
#include "sceneobject.h"
#include "light.h"

  


/* 
  -----------------
  Global variables:
  -----------------
*/

/* Size of the drawing canvas. */
extern int CANVAS_WIDTH;
extern int CANVAS_HEIGHT;

/* The center point where the camera is located. This is where the camera
   sits in relation to the scene. */
extern Vector CAMERA_LOCATION;

/* Viewing parameters: */
extern GLfloat P_NEAR;  /* Distance from viewpoint to image plane. */
extern GLfloat FOV_X;  /* X-angle of view frustum. */

/* Pointer to a STL vector containing all the objects of the scene. */
extern vector <SceneObject *> *SCENE_OBJECTS;

/* Pointer to a STL vector containing all the lights of the scene. */
extern vector <PointLight *> *SCENE_LIGHTS;

/* Color of the background. */
extern Color BG_COLOR;

/* Color of the ambient light in the scene. */
extern Color AMBIENT_COLOR;

/* Rays will be shot until reaching this depth. */
extern int MAX_TRACING_DEPTH;

/* The refraction index of the material the current ray is coming from. */
extern double INCOMING_REFRACTION_INDEX;

/* 
  ----------------------
  Function declarations:
  ----------------------
*/

/* Sets up the scene. */
void initScene(void);


/* Main function that will draw the raytraced scene when called. */
void drawScene(void);


/* Takes a point in Vector form and a direction from the point in Vector form, then
   traces a ray for DEPTH times to sample the color for the point. Returns the color. */
Color traceRay(const Vector &rayStartPoint, const Vector &rayDirection, int depth);


/* Takes a point and a direction from that point to form a ray.
   This function will attempt to find the first object that intersects with the ray and return 
   a boolean indicating success/failure.

   Upon success, the function will return true, the point of intersection will be placed in INTERSECTION_POINT,
   and the intersecting object will be placed into INTERSECTION_OBJECT.

   Upon failure, false will simply be returned. 
*/
bool findFirstIntersection(const Vector &rayStartPoint, const Vector &rayDirection, Vector &intersectionPoint, SceneObject &intersectionObject);


/* Takes a point in Vector form and a direction from the point in Vector form, then
   traces a ray for DEPTH times to sample the color for the point. Returns the color. */
Color traceRay(const Vector &rayStartPoint, const Vector &rayDirection, int depth);


/* Takes a point and a direction from that point to form a ray.
   This function will find the color of this ray at INTERSECTION_POINT on INTERSECTION_OBJECT using the phong reflection model.
*/
Color getPhong(const Vector &rayStartPoint, const Vector &rayDirection, const Vector &intersectionPoint, const SceneObject &intersectionObject);


/* Takes a point and returns a value between 0.0 and 1.0 representing how occluded the point is based on the scene lighting. */
double getShadowAmount(const Vector &point);


/* Returns true if the OBJECT is a light, false otherwise. */
bool isLight(const SceneObject &object);


#endif	/* _RAYTRACE_H_ */
