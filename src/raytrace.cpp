/* Contains definitions for functions and variables that handle the raytracing process.
   This is where all the raytracing is done.
*/

#ifdef _WIN32
#include <windows.h>
#endif
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <list>
#include <typeinfo>
#include <vector> /* STL vector. */
#include "common.h"
#include "lowlevel.h"
#include "raytrace.h"
#include "vector.h" /* My own implementation of a 4x1 vector. */
#include "color.h"
#include "misc.h"
#include "test.h"
#include "sceneobject.h"
#include "geometry.h"
#include "light.h"
#include "transform.h"

using namespace std;


/* local functions */
void initCamera (int, int);
void display(void);
void init(int, int);


/* Viewing parameters: */
GLfloat P_NEAR;  /* distance from viewpoint to image plane */
GLfloat FOV_X;  /* x-angle of view frustum */

/* The center point where the camera is located. This is where the camera
   sits in relation to the scene. */
Vector CAMERA_LOCATION;


/* Scene parameters: */
/* Pointer to a STL vector containing all the objects of the scene. */
vector <SceneObject *> *SCENE_OBJECTS;

/* Pointer to a STL vector containing all the lights of the scene. */
vector <PointLight *> *SCENE_LIGHTS;

/* Color of the background. */
Color BG_COLOR = {0.10, 0.0, 0.10, 1.0};

/* Color of the ambient light in the scene. */
Color AMBIENT_COLOR = {0.03125, 0.0, 0.0625, 1.0};


int CANVAS_WIDTH = 500;     /* CANVAS_WIDTH of window in pixels */
int CANVAS_HEIGHT = 300;    /* CANVAS_HEIGHT of window in pixels */

/* Rays will be shot until reaching this depth. */
int MAX_TRACING_DEPTH = 6;

/* The refraction index of the material the current ray is coming from. */
double INCOMING_REFRACTION_INDEX = 1.0;



int main (int argc, char** argv) {
  int win;

  glutInit(&argc,argv);
  glutInitWindowSize(CANVAS_WIDTH,CANVAS_HEIGHT);
  glutInitWindowPosition(100,100);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  win = glutCreateWindow("raytrace");
  glutSetWindow(win);
  init(CANVAS_WIDTH,CANVAS_HEIGHT);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}


void init(int w, int h) {

  /* OpenGL setup */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
  glClearColor(0.0, 0.0, 0.0, 0.0);  

  /* low-level graphics setup */
  initCanvas(w,h);

  /* raytracer setup */
  initCamera(w,h);

  initScene();
}


void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  // test();
  drawScene();
  flushCanvas();  /* draw the canvas to the OpenGL window */
  glFlush();
}


void initCamera (int w, int h) {
  P_NEAR = 1.0;
  FOV_X = PI/6;
  CAMERA_LOCATION = Vector(0, 0, 0, 1);
}



/* Sets up the scene. */
void initScene(void) {

    SCENE_OBJECTS = new vector <SceneObject *>;
    SCENE_LIGHTS = new vector <PointLight *>;
    
    PointLight *light1 = new PointLight(); {
        light1->x() =  0;
        light1->y() =  10;
        light1->z() = -15.0;
        light1->intensity = 2.0;
        
        light1->material.color.r = 0.0;
        light1->material.color.g = 0.0;
        light1->material.color.b = 1.0;

        SCENE_LIGHTS->push_back(light1);
        SCENE_OBJECTS->push_back(light1);
    }


    PointLight *light2 = new PointLight(); {
        light2->x() =  20.0;
        light2->y() = -1.5;
        light2->z() = 15.0;
        light2->intensity = 2.0;

        light2->material.color.r = 1.0;
        light2->material.color.g = 1.0;
        light2->material.color.b = 0.0;

        SCENE_LIGHTS->push_back(light2);
        SCENE_OBJECTS->push_back(light2);
    }


    PointLight *light3 = new PointLight(); {
        light3->x() =  -20.0;
        light3->y() = 10.0;
        light3->z() = 12.5;
        light3->intensity = 3.0;

        light3->material.color.r = 1.0;
        light3->material.color.g = 0.0;
        light3->material.color.b = 0.0;

        SCENE_LIGHTS->push_back(light3);
        SCENE_OBJECTS->push_back(light3);
    }


    unsigned int maxSpheres = 22;

    /* Create a ring of spheres in the scene. */
    for (unsigned int i = 0; i < maxSpheres; i++) {
        Sphere *s = new Sphere; {
            
            s->radius = (1.0*i/(4*maxSpheres)) + (2.25/maxSpheres);

            s->x() = 2*cos( 2.0*PI*i/maxSpheres) + 3.25*i/maxSpheres - 2.00;
            s->y() = 2*sin( 2.0*PI*i/maxSpheres) + 2.75*i/maxSpheres - 1.00;
            s->z() = 2*s->radius - 12.0;
            
            s->material.color.r = (2.0*i/(maxSpheres));
            s->material.color.g = (2.0*i/(maxSpheres));
            s->material.color.b = 0.00;
            s->material.ambient = 0.1;
            s->material.specular = 0.90;
            s->material.shininess = 5;

            

            SCENE_OBJECTS->push_back(s);
        }
    }


    /* Create a central sphere. */
    Sphere *s = new Sphere; {
        s->radius = 2.0;

        s->x() =  0;
        s->y() =  0;
        s->z() = -15.0;

        s->material.color.r = 1.00;
        s->material.color.g = 0.0;
        s->material.color.b = 0.0;
        s->material.color.a = 0.30;
        s->material.ambient = 0.1;
        s->material.specular = 0.95;
        s->material.shininess = 3;
        s->material.refraction = 2.0;

        SCENE_OBJECTS->push_back(s);
    }


    /* Create a background plane. */
    Plane *p1 = new Plane; {
        p1->normal = Vector (0.0, 0.0, 1.0, 0.0);

        p1->x() =  0;
        p1->y() =  0;
        p1->z() = -25.0;

        p1->material.color.r = 0.0;
        p1->material.color.g = 0.0;
        p1->material.color.b = 0.3;
        p1->material.color.a = 1.0;
        p1->material.ambient = 1.0;
        p1->material.specular = 0.95;
        p1->material.shininess = 20;

        SCENE_OBJECTS->push_back(p1);
    }

    /* Create a background plane. */
    Plane *p2 = new Plane; {
        p2->normal = Vector (0.0, 0.0, -1.0, 0.0);

        p2->x() =  0;
        p2->y() =  0;
        p2->z() = 10.0;

        p2->material.color.r = 0.0;
        p2->material.color.g = 0.0;
        p2->material.color.b = 0.3;
        p2->material.color.a = 0.5;
        p2->material.ambient = 1.0;
        p2->material.specular = 0.95;
        p2->material.shininess = 20;

        SCENE_OBJECTS->push_back(p2);
    }

    Plane *p3 = new Plane; {
        p3->normal = Vector (0.0, 1.0, 0.0, 0.0);

        p3->x() =  0;
        p3->y() = -3.00;
        p3->z() =  0;

        p3->material.color.r = 0.0;
        p3->material.color.g = 0.0;
        p3->material.color.b = 0.3;
        p3->material.color.a = 1.0;
        p3->material.ambient = 1.0;
        p3->material.specular = 0.55;
        p3->material.shininess = 100;

        SCENE_OBJECTS->push_back(p3);
    }

    /* Create a triangle. */
    Triangle *t0 = new Triangle; {

        t0->vertex0 = Vector (-1.5+3 , 0, -5, 1);
        t0->vertex1 = Vector (0+3    , 2, -5, 1);
        t0->vertex2 = Vector (1.5+3  , 0, -5, 1);

        t0->material.color.r = 0.5;
        t0->material.color.g = 0.0;
        t0->material.color.b = 0.5;
        t0->material.color.a = 0.30;
        t0->material.ambient = 0.3;
        t0->material.specular = 0.05;
        t0->material.shininess = 500;
        t0->material.refraction = 2.0;

        SCENE_OBJECTS->push_back(t0);
    }

    Triangle *t1 = new Triangle; {

        t1->vertex0 = Vector (-1.5+5 , 1, -8, 1);
        t1->vertex1 = Vector (0+5    , 3, -8, 1);
        t1->vertex2 = Vector (1.5+5  , 1, -8, 1);

        t1->material.color.r = 1.0;
        t1->material.color.g = 0.0;
        t1->material.color.b = 0.0;
        t1->material.color.a = 0.30;
        t1->material.ambient = 0.3;
        t1->material.specular = 0.05;
        t1->material.shininess = 500;
        t1->material.refraction = 2.0;

        SCENE_OBJECTS->push_back(t1);
    }


    /* Tetrahedron 0. */
    Vector tetra0Vertex0 (-2-8.0,  0-4.0,  0-12.5, 1);
    Vector tetra0Vertex1 ( 0.5-8.5,  1.25-3.5,  -3-12.5, 1);
    Vector tetra0Vertex2 ( 1.75-8.5,  .25-3.5,  0-12.5, 1);
    Vector tetra0Vertex3 ( 0-8.5,  2.5-3.5, -2-12.5, 1);
    Triangle *tetra0T1 = new Triangle; {
        tetra0T1->vertex0 = tetra0Vertex0;        
        tetra0T1->vertex1 = tetra0Vertex1; 
        tetra0T1->vertex2 = tetra0Vertex2;

        tetra0T1->material.color.r = 0.8;
        tetra0T1->material.color.g = 0.8;
        tetra0T1->material.color.b = 0.0;
        tetra0T1->material.color.a = 0.80;
        tetra0T1->material.ambient = 0.01;
        tetra0T1->material.specular = 1.00;
        tetra0T1->material.shininess = 15.0;
        tetra0T1->material.refraction = 2.0;

        SCENE_OBJECTS->push_back(tetra0T1);
    } 
        Triangle *tetra0T2 = new Triangle; {
        tetra0T2->vertex0 = tetra0Vertex0;        
        tetra0T2->vertex1 = tetra0Vertex1; 
        tetra0T2->vertex2 = tetra0Vertex3;

        tetra0T2->material.color.r = 0.8;
        tetra0T2->material.color.g = 0.8;
        tetra0T2->material.color.b = 0.0;
        tetra0T2->material.color.a = 0.80;
        tetra0T2->material.ambient = 0.01;
        tetra0T2->material.specular = 1.05;
        tetra0T2->material.shininess = 15.0;
        tetra0T2->material.refraction = 2.0;

        SCENE_OBJECTS->push_back(tetra0T2);
    } 
        Triangle *tetra0T3 = new Triangle; {
        tetra0T3->vertex0 = tetra0Vertex0;        
        tetra0T3->vertex1 = tetra0Vertex2; 
        tetra0T3->vertex2 = tetra0Vertex3;

        tetra0T3->material.color.r = 0.8;
        tetra0T3->material.color.g = 0.8;
        tetra0T3->material.color.b = 0.0;
        tetra0T3->material.color.a = 0.80;
        tetra0T3->material.ambient = 0.01;
        tetra0T3->material.specular = 1.0;
        tetra0T3->material.shininess = 15.0;
        tetra0T3->material.refraction = 2.0;

        SCENE_OBJECTS->push_back(tetra0T3);
    } 
        Triangle *tetra0T4 = new Triangle; {
        tetra0T4->vertex0 = tetra0Vertex1;        
        tetra0T4->vertex1 = tetra0Vertex2; 
        tetra0T4->vertex2 = tetra0Vertex3;

        tetra0T4->material.color.r = 0.8;
        tetra0T4->material.color.g = 0.8;
        tetra0T4->material.color.b = 0.0;
        tetra0T4->material.color.a = 0.80;
        tetra0T4->material.ambient = 0.01;
        tetra0T4->material.specular = 1.00;
        tetra0T4->material.shininess = 15.0;
        tetra0T4->material.refraction = 2.0;

        SCENE_OBJECTS->push_back(tetra0T4);
    } 


    /* Tetrahedron 1. */
    Vector tetra1Vertex0 (-2+8.0,  0+4.0,  0-12.5, 1);
    Vector tetra1Vertex1 ( -0.5+8.5,  1.25+3.5,  -3-12.5, 1);
    Vector tetra1Vertex2 ( 1.75+8.5,  .25+3.5,  0-12.5, 1);
    Vector tetra1Vertex3 ( 0+8.5,  3.0+3.5, -2-12.5, 1);

    Triangle *tetra1T1 = new Triangle; {
        tetra1T1->vertex0 = tetra1Vertex0;        
        tetra1T1->vertex1 = tetra1Vertex1; 
        tetra1T1->vertex2 = tetra1Vertex2;

        tetra1T1->material.color.r = 0.5;
        tetra1T1->material.color.g = 1.0;
        tetra1T1->material.color.b = 0.0;
        tetra1T1->material.color.a = 0.80;
        tetra1T1->material.ambient = 0.00;
        tetra1T1->material.specular = 0.90;
        tetra1T1->material.shininess = 50;
        tetra1T1->material.refraction = 2.0;

        SCENE_OBJECTS->push_back(tetra1T1);
    } 
        Triangle *tetra1T2 = new Triangle; {
        tetra1T2->vertex0 = tetra1Vertex0;        
        tetra1T2->vertex1 = tetra1Vertex1; 
        tetra1T2->vertex2 = tetra1Vertex3;

        tetra1T2->material.color.r = 0.5;
        tetra1T2->material.color.g = 1.0;
        tetra1T2->material.color.b = 0.0;
        tetra1T2->material.color.a = 0.80;
        tetra1T2->material.ambient = 0.00;
        tetra1T2->material.specular = 0.90;
        tetra1T2->material.shininess = 50;
        tetra1T2->material.refraction = 2.0;

        SCENE_OBJECTS->push_back(tetra1T2);
    } 
        Triangle *tetra1T3 = new Triangle; {
        tetra1T3->vertex0 = tetra1Vertex0;        
        tetra1T3->vertex1 = tetra1Vertex2; 
        tetra1T3->vertex2 = tetra1Vertex3;

        tetra1T3->material.color.r = 0.5;
        tetra1T3->material.color.g = 1.0;
        tetra1T3->material.color.b = 0.0;
        tetra1T3->material.color.a = 0.80;
        tetra1T3->material.ambient = 0.00;
        tetra1T3->material.specular = 0.90;
        tetra1T3->material.shininess = 50;
        tetra1T3->material.refraction = 2.0;

        SCENE_OBJECTS->push_back(tetra1T3);
    } 
        Triangle *tetra1T4 = new Triangle; {
        tetra1T4->vertex0 = tetra1Vertex1;        
        tetra1T4->vertex1 = tetra1Vertex2; 
        tetra1T4->vertex2 = tetra1Vertex3;

        tetra1T4->material.color.r = 0.5;
        tetra1T4->material.color.g = 1.0;
        tetra1T4->material.color.b = 0.0;
        tetra1T4->material.color.a = 0.80;
        tetra1T4->material.ambient = 0.00;
        tetra1T4->material.specular = 0.90;
        tetra1T4->material.shininess = 50;
        tetra1T4->material.refraction = 2.0;

        SCENE_OBJECTS->push_back(tetra1T4);
    } 





}



void drawScene (void) {

    GLfloat imageWidth;


    /* The current pixel to draw in world coordinates. */
    Vector currentPixelWorldCoord (0, 0, -P_NEAR, 1.0);

    /* A ray will be shot through the current pixel in this direction. */
    Vector rayDirection;

    /* Color of the pixel to draw. */
    Color currentPixelColor;


    /* FOV_X is the x angle of the view frustrum. */
    imageWidth = 2*P_NEAR*tan(FOV_X/2);

    /* Trace a ray for every pixel in the canvas. */
    for (int i = 0; i < CANVAS_WIDTH; i++) {

        for (int j = 0; j < CANVAS_HEIGHT; j++) {

            /* Find position of the current pixel in world coordinates. */
            
            /* (i-(CANVAS_WIDTH/2)) creates an x-axis from -(CANVAS_WIDTH/2) to (CANVAS_WIDTH/2). 
               imageWidth/CANVAS_WIDTH gives the ratio to convert to world coordinates. */
            currentPixelWorldCoord[0] = (i-(CANVAS_WIDTH/2))*imageWidth/CANVAS_WIDTH;

             /* (j-(CANVAS_HEIGHT/2)) creates an y-axis from -(CANVAS_HEIGHT/2) to (CANVAS_HEIGHT/2). 
                imageWidth/CANVAS_WIDTH gives the ratio to convert to world coordinates. */
            currentPixelWorldCoord[1] = (j-(CANVAS_HEIGHT/2))*imageWidth/CANVAS_WIDTH;
            

            /* rayDirection should the vector starting at the camera that passes directly through 
               the current pixel to draw. */
            rayDirection = (currentPixelWorldCoord - CAMERA_LOCATION).normalize();

            
            /* Trace the ray back from the pixel location and get the color to draw it as. */
            currentPixelColor = traceRay(currentPixelWorldCoord, rayDirection, 0);

            /* Write the pixel back to the screen. */
            drawPixel(i, j, currentPixelColor.r, currentPixelColor.g, currentPixelColor.b);
        }
    }
}



/* Takes a point and a direction that define a ray, then traces the ray for DEPTH 
   times to determine the color for the ray's start point. Returns the color. */
Color traceRay(const Vector &rayStartPoint, const Vector &rayDirection, int depth) {

    if (depth > MAX_TRACING_DEPTH) {
        /* Return background color. */
        return BG_COLOR;
    }

    Color localColor = {0.0, 0.0, 0.0, 1.0};
    Color reflectedColor = {0.0, 0.0, 0.0, 1.0};
    Color transmittedColor = {0.0, 0.0, 0.0, 1.0};
    Color finalColor = {0.0, 0.0, 0.0, 1.0};

    Vector intersectionPoint (0.0, 0.0, 0.0, 1.0);
    Vector intersectionPointNormal;

    SceneObject intersectionObject;

    /* Takes a point and a direction from that point to form a ray, and a depth of raytracing recursion.
       This function will attempt to find the first object that intersects with the ray.
       Upon success, the function will return true, the first object that intersects with the ray will 
       be placed into INTERSECTION_OBJECT, and the point of intersection will be placed in INTERSECTION_POINT. 
       Upon failure, false will simply be returned. */
    //bool intersection = findFirstIntersection(rayStartPoint, rayDirection, depth, intersectionPoint, intersectionObject);
    bool intersection = findFirstIntersection(rayStartPoint, rayDirection, intersectionPoint, intersectionObject);


    /* If there was no intersection, then return the background color. */
    if (!intersection) {
        /* Return background color. */
        return BG_COLOR;
    }

    /* If the ray intersected with the light, then return the light color, minus any attenuation. */
    if (isLight(intersectionObject)) {
        cout << "IS LIGHT!" << endl;
        return intersectionObject.material.color;
    }


    /* Get base color for the point. */
    localColor = getPhong(rayStartPoint, rayDirection, intersectionPoint, intersectionObject);
    
    /* Get the color of any reflections on the point. */
    Vector cameraToIntersectionPointUnitVector = (CAMERA_LOCATION - intersectionPoint).normalize();
    Vector intersectionObjectUnitNormal = intersectionObject.getNormal(intersectionPoint).normalize();
    Vector reflectionUnitVector = 2*cameraToIntersectionPointUnitVector.dotProduct(intersectionObjectUnitNormal)*intersectionObjectUnitNormal - cameraToIntersectionPointUnitVector;

    reflectedColor = traceRay(intersectionPoint + 0.001*reflectionUnitVector, reflectionUnitVector, depth+1);

    /* If the point is translucent, shoot a refraction/translucency ray to find the color behind the point. */
    if (intersectionObject.material.color.a < 1.0)  {
        transmittedColor = traceRay(intersectionPoint + 0.001*rayDirection, rayDirection, depth+1);
    }


    finalColor = intersectionObject.material.color.a*localColor + intersectionObject.material.specular*reflectedColor + (1-intersectionObject.material.color.a)*transmittedColor;

    /* Clamp the final color's values to be between 0.0 and 1.0 to prevent color distortion. */
    clamp(finalColor, 0.0, 1.0);


    return finalColor;
}



/* Takes a point and a direction from that point to form a ray, and a depth of raytracing recursion.
   This function will attempt to find the first object that intersects with the ray and return 
   a boolean indicating success/failure.

   Upon success, the function will return true, the point of intersection will be placed in INTERSECTION_POINT,
   and the intersecting object will be placed into INTERSECTION_OBJECT.

   Upon failure, false will simply be returned. 
*/
bool findFirstIntersection(const Vector &rayStartPoint, const Vector &rayDirection, Vector &intersectionPoint, SceneObject &intersectionObject) {

    /* List of pointers to all objects that intersect with the current ray. 
       *** NOTE: *** intersectionPoints[i] corresponds to intersections[i]. */
    vector <SceneObject *> intersections;

    /* List of intersection points for the corresponding ray-intersecting objects in intersectionPoints. */
    vector <Vector> intersectionPoints;

    /* currentObjectPointer points to the current object we're testing intersection for in SCENE_OBJECTS. */
    SceneObject *currentObjectPointer;


    bool currentObjectIntersects;
    Vector currentObjectIntersectionPoint (0.0, 0.0, 0.0, 1.0);

    /* Find all objects that intersect with ray. */
    for (unsigned int i = 0; i < SCENE_OBJECTS->size(); i++) {

        currentObjectPointer = (*SCENE_OBJECTS)[i];
        currentObjectIntersects = currentObjectPointer->checkIntersection(rayStartPoint, rayDirection, currentObjectIntersectionPoint);
        
        if (currentObjectIntersects) {
            intersections.push_back((*SCENE_OBJECTS)[i]);
            intersectionPoints.push_back(currentObjectIntersectionPoint);
        }
    }


    /* If no intersections were found, returns with failure. */
    if (intersections.empty()) {
        return false;

    }


    /* Go through all of the intersection points and find the one closest to the ray's start point. 
       That intersection point is what will be returned. */

    /* We save the index of the closest point and the closest point's distance. */
    unsigned int closestSceneObject = 0;
    unsigned int closestSceneObjectPoint = 0;

    /* Closest distance found so far. */
    double closestDistance = rayStartPoint.distance(intersectionPoints[0]);

    /* Distance of the current iteration. */
    double currentDistance;

    /* Find the object closest to the starting point of the ray. */
    for (unsigned int i = 0; i < intersections.size(); i++) {

        /* If we find a closer distance, store the information. */
        if ((currentDistance = rayStartPoint.distance(intersectionPoints[i])) < closestDistance) {
            closestDistance = currentDistance;
            closestSceneObject = i;
            closestSceneObjectPoint = i;
        }
    }


    /* Put the closest point and closest object into variables that will be returned to caller function. */
    intersectionPoint = intersectionPoints[closestSceneObjectPoint];
    intersectionObject = *intersections[closestSceneObject];


    return true;
}





/* Takes a point and a direction from that point to form a ray.
   This function will find the color of this ray at INTERSECTION_POINT on INTERSECTION_OBJECT using the phong reflection model.
*/
Color getPhong(const Vector &rayStartPoint, const Vector &rayDirection, const Vector &intersectionPoint, const SceneObject &intersectionObject) {

    /* Coefficients for each component of Phong shading. Used to calculate the actual color of each Phong component. */
    double diffuseCoefficient = 0;
    double specularCoefficient = 0;

    Color diffuseColor;
    Color specularColor;

    Color phong = {0.0, 0.0, 0.0, 1.0};

    

    /* Unit vector orthagonal to the point where the ray intersects the object. */
    Vector intersectionPointUnitNormal;

    /* Unit vector from the intersection point to the current light source. */
    Vector directionToLightUnitVector;

    /* Unit vector representing the reflected ray from the intersection point. */
    Vector reflectionUnitVector;

    /* Unit vector in the direction of the ray. */
    Vector rayDirectionUnitVector = rayDirection;
    rayDirectionUnitVector.normalize();

    /* Unit vector pointing to the camera. */
    Vector cameraDirectionUnitVector = (CAMERA_LOCATION - intersectionPoint).normalize();

    /* cos(angle between incoming light and direction to camera). Used for specular highlights. */
    double angleBetweenCameraAndLight = 0.0;

    /* Pointer to the current light that we are inspecting. */
    PointLight *currentLightPointer;



    /* Go through each light and determine the phong shading for the intersction point using that light. 
       Add together all these shadings for a final intersection point color. */
    for (unsigned int i = 0; i < SCENE_LIGHTS->size(); i++) {

        currentLightPointer = (*SCENE_LIGHTS)[i];

        intersectionPointUnitNormal = intersectionObject.getNormal(intersectionPoint).normalize();  
        directionToLightUnitVector = (currentLightPointer->position - intersectionPoint).normalize();
        reflectionUnitVector = (2*(directionToLightUnitVector.dotProduct(intersectionPointUnitNormal)*intersectionPointUnitNormal) - directionToLightUnitVector).normalize();
        

        angleBetweenCameraAndLight = reflectionUnitVector.dotProduct(cameraDirectionUnitVector);
        /* If the angle is negative, that means the reflected specular ray is facing away from camera and no specular highlight should occur. */
        angleBetweenCameraAndLight = max(angleBetweenCameraAndLight, 0.0);


        /* Diffuse shading at intersection point. */
        diffuseCoefficient = max(0.0, directionToLightUnitVector.dotProduct(intersectionPointUnitNormal));
        diffuseColor = (diffuseCoefficient * intersectionObject.material.diffuse) * (currentLightPointer->getColor(intersectionPoint) + intersectionObject.getColor(intersectionPoint));

        /* Specular shading at intersection point. */
        specularCoefficient = pow(angleBetweenCameraAndLight, intersectionObject.material.shininess);
        specularColor = (specularCoefficient * intersectionObject.material.specular) * (currentLightPointer->getColor(intersectionPoint) + intersectionObject.getColor(intersectionPoint));


        /* Compute the shadow amount at intersection point. */
        Vector shadowRayIntersectionPoint;
        SceneObject shadowRayIntersectionObject;

        findFirstIntersection(intersectionPoint + 0.001*directionToLightUnitVector, directionToLightUnitVector, shadowRayIntersectionPoint, shadowRayIntersectionObject);
        if (shadowRayIntersectionPoint != currentLightPointer->position) {
            diffuseColor *= 0.25 * currentLightPointer->getIntensity(intersectionPoint);
            specularColor *= currentLightPointer->getIntensity(intersectionPoint);
        }


        /* Intersection point color composed of the phong shading from every light inspected so far. */
        phong += diffuseColor + specularColor;

    }

    /* Assembled phong shading for the pixel. */
    phong += AMBIENT_COLOR * intersectionObject.material.ambient;

    return phong;
}



/* Returns true if the OBJECT is a light, false otherwise. */
bool isLight(const SceneObject &object) {
    return dynamic_cast<const PointLight *>(&object);
}




