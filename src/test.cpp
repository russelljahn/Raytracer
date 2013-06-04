/* Contains definitions for functions used to test correctness of components of the program. */

#include <iostream>
#include <cstdio>
#include <cmath>

#include "test.h"
#include "color.h"
#include "sceneobject.h"
#include "geometry.h"
#include "raytrace.h"
#include "lowlevel.h"
#include "vector.h"

using namespace std;



void test(void) {
	//testColor();
	//testScene();
	testVector();
	// testSphereIntersection();
}



void testColor(void) {
	cout << "------------------------" << endl;
	cout << "Testing color struct... " << endl;
	cout << "------------------------" << endl;

	Color c1 = {.5, .5, .5, .5};
	Color c2 = {2, 3, 4, 5};
	Color c3 = {.35, .5, .1, 0.0};

	cout << "c1: " << c1 << endl;
	cout << "c2: " << c2 << endl;
	cout << "c3: " << c3 << endl;


	cout << "c1+c2: " << c1+c2 << endl;
	cout << "c1-c2: " << c1-c2 << endl;

	cout << "c2+c1: " << c2+c1 << endl;
	cout << "c2-c1: " << c2-c1 << endl;

	cout << "c1+c3: " << c1+c3 << endl;
	cout << "c1-c3: " << c1-c3 << endl;

	cout << "c3+c1: " << c3+c1 << endl;
	cout << "c3-c1: " << c3-c1 << endl;

}



void testScene(void) {
	cout << "------------------------" << endl;
	cout << "Testing Scene...        " << endl;
	cout << "------------------------" << endl;


	// for (unsigned int i = 0; i < SCENE_OBJECTS->size(); i++) {
		// cout << "SceneObject " << i << ": " << *(*SCENE_OBJECTS)[i] << endl;
	// }
}





void testVector(void) {
	Vector a (1, 0, 0, 1);
	Vector b (0, 1, 0, 1);
	Vector c (0, 0, 0, 0);
	Vector d (5, 0, 4, 1);
	Vector e (.99, .03, 0, 1);
	Vector f (1, 0, 98.76754, 1);
	Vector g (1, -1, 1, 1);
	Vector h (-411.14, 27, -999000, 1);

	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl;
	cout << "d: " << d << endl;
	cout << "e: " << e << endl;
	cout << "f: " << f << endl;
	cout << "g: " << g << endl;
	cout << "h: " << h << endl;

	cout << "a.crossProduct(a): " << a.crossProduct(a) << endl;
	cout << "a.crossProduct(b): " << a.crossProduct(b) << endl;
	cout << "a.crossProduct(c): " << a.crossProduct(c) << endl;
	cout << "a.crossProduct(d): " << a.crossProduct(d) << endl;
	cout << "a.crossProduct(e): " << a.crossProduct(e) << endl;
	cout << "a.crossProduct(f): " << a.crossProduct(f) << endl;
	cout << "a.crossProduct(g): " << a.crossProduct(g) << endl;
	cout << "a.crossProduct(h): " << a.crossProduct(h) << endl;

	cout << "b.crossProduct(a): " << b.crossProduct(a) << endl;
	cout << "b.crossProduct(b): " << b.crossProduct(b) << endl;
	cout << "b.crossProduct(c): " << b.crossProduct(c) << endl;
	cout << "b.crossProduct(d): " << b.crossProduct(d) << endl;
	cout << "b.crossProduct(e): " << b.crossProduct(e) << endl;
	cout << "b.crossProduct(f): " << b.crossProduct(f) << endl;
	cout << "b.crossProduct(g): " << b.crossProduct(g) << endl;
	cout << "b.crossProduct(h): " << b.crossProduct(h) << endl;

	cout << "c.crossProduct(a): " << c.crossProduct(a) << endl;
	cout << "c.crossProduct(b): " << c.crossProduct(b) << endl;
	cout << "c.crossProduct(c): " << c.crossProduct(c) << endl;
	cout << "c.crossProduct(d): " << c.crossProduct(d) << endl;
	cout << "c.crossProduct(e): " << c.crossProduct(e) << endl;
	cout << "c.crossProduct(f): " << c.crossProduct(f) << endl;
	cout << "c.crossProduct(g): " << c.crossProduct(g) << endl;
	cout << "c.crossProduct(h): " << c.crossProduct(h) << endl;

	cout << "e.crossProduct(f): " << e.crossProduct(f) << endl;
	cout << "f.crossProduct(e): " << f.crossProduct(e) << endl;

	cout << "e.crossProduct(h): " << e.crossProduct(h) << endl;
	cout << "h.crossProduct(e): " << h.crossProduct(e) << endl;

	cout << "f.crossProduct(h): " << f.crossProduct(h) << endl;
	cout << "h.crossProduct(f): " << h.crossProduct(f) << endl;
}





void testSphereIntersection(void) {

	bool intersection;
	Vector returnIntersectionPoint;

	Sphere a = Sphere(10, 10, 10, 5);
	cout << "a: " << a << endl;

	Vector rayDirectionA = Vector(1, 1, 1, 1);

	Vector rayStartA = Vector(0, 0, 0, 1);
	Vector rayStartF = Vector(4, 0, 0, 1);
	Vector rayStartB = Vector(5, 0, 0, 1);
	Vector rayStartC = Vector(6, 0, 0, 1);
	Vector rayStartD = Vector(7, 0, 0, 1);
	Vector rayStartE = Vector(8, 0, 0, 1);
	// Vector rayStartF;
	Vector rayStartG;
	Vector rayStartH;
	Vector rayStartI;
	Vector rayStartJ;
	Vector rayStartK;
	Vector rayStartL;

	rayStartA = Vector(0, 0, 0, 1);
	rayStartB = Vector(0, 1, 0, 1);
	rayStartC = Vector(0, 2, 0, 1);
	rayStartD = Vector(0, 3, 0, 1);
	rayStartK = Vector(0, 3.99, 0, 1);
	rayStartE = Vector(0, 4, 0, 1);
	rayStartL = Vector(0, 4.01, 0, 1);
	rayStartF = Vector(0, 4.50, 0, 1);
	rayStartG = Vector(0, 5, 0, 1);
	rayStartH = Vector(0, 6, 0, 1);
	rayStartI = Vector(0, 7, 0, 1);
	rayStartJ = Vector(0, 8, 0, 1);
   
    

    intersection = a.checkIntersection(rayStartA, rayDirectionA, returnIntersectionPoint);
	cout << "Testing ray a: " << intersection << endl;
	intersection = a.checkIntersection(rayStartB, rayDirectionA, returnIntersectionPoint);
	cout << "Testing ray b: " << intersection << endl;
	intersection = a.checkIntersection(rayStartC, rayDirectionA, returnIntersectionPoint);
	cout << "Testing ray c: " << intersection << endl;
	intersection = a.checkIntersection(rayStartD, rayDirectionA, returnIntersectionPoint);
	cout << "Testing ray d: " << intersection << endl;
	intersection = a.checkIntersection(rayStartE, rayDirectionA, returnIntersectionPoint);
	cout << "Testing ray e: " << intersection << endl;
	intersection = a.checkIntersection(rayStartF, rayDirectionA, returnIntersectionPoint);
	cout << "Testing ray f: " << intersection << endl;
	intersection = a.checkIntersection(rayStartG, rayDirectionA, returnIntersectionPoint);
	cout << "Testing ray g: " << intersection << endl;
    intersection = a.checkIntersection(rayStartH, rayDirectionA, returnIntersectionPoint);
	cout << "Testing ray h: " << intersection << endl;
	intersection = a.checkIntersection(rayStartI, rayDirectionA, returnIntersectionPoint);
	cout << "Testing ray i: " << intersection << endl;
	intersection = a.checkIntersection(rayStartJ, rayDirectionA, returnIntersectionPoint);
	cout << "Testing ray j: " << intersection << endl;
	intersection = a.checkIntersection(rayStartK, rayDirectionA, returnIntersectionPoint);
	cout << "Testing ray k: " << intersection << endl;
	intersection = a.checkIntersection(rayStartL, rayDirectionA, returnIntersectionPoint);
	cout << "Testing ray l: " << intersection << endl;



	return;

    GLfloat imageWidth;
    /* declare data structures on stack to avoid dynamic allocation */
    // point worldPix;  /* current pixel in world coordinates */
    Vector worldPixel;

    // point direction; 
    // ray r;
    // Color c;

    Vector rayStartPoint;
    Vector rayDirection;
    

    /* initialize */
    // worldPix.w = 1.0;
    // worldPix.z = -P_NEAR;
    worldPixel[2] = -P_NEAR;
    worldPixel[3] = 1.0;

    // r.start = &worldPix;
    // r.dir= &direction;

    imageWidth = 2*P_NEAR*tan(FOV_X/2);

    /* trace a ray for every pixel */
    for (int i = 0; i < CANVAS_WIDTH; i++) {
    /* Refresh the display */
    /* Comment this line out after debugging */
    flushCanvas();

        for (int j = 0; j < CANVAS_HEIGHT; j++) {

            /* find position of pixel in world coordinates */
            
            /* x position = (pixel CANVAS_WIDTH/middle) scaled to world coords */ 
            // worldPix.x = (i-(CANVAS_WIDTH/2))*imageWidth/CANVAS_WIDTH;
            worldPixel[0] = (i-(CANVAS_HEIGHT/2))*imageWidth/CANVAS_WIDTH;

            /* y position = (pixel CANVAS_HEIGHT/middle) scaled to world coords */ 
            // worldPix.y = (j-(CANVAS_HEIGHT/2))*imageWidth/CANVAS_WIDTH;
            worldPixel[1] = (j-(CANVAS_HEIGHT/2))*imageWidth/CANVAS_WIDTH;
            
            cout << worldPixel << endl;


            printf("x: %i, y: %i, ", i, j);

            /* find direction */
            /* note: direction vector is NOT NORMALIZED */

            // calculateDirection(viewpoint,&worldPix,&direction);
            rayDirection = worldPixel - CAMERA_LOCATION;

            Vector returnIntersectionPoint;
            // SceneObject *s1 = (*SCENE_OBJECTS)[0];
            // cout << "s1: " << *s1 << endl;
            // bool intersection = s1->checkIntersection(rayStartPoint, rayDirection, returnIntersectionPoint);

			if (intersection) {
			    printf("HIT!\n");
			}
			else {
			    printf("miss...\n");
			}
            /* trace the ray! */
            // traceRay(&r,&c,0);
            /* write the pixel! */
            // drawPixel(i,j,c.r,c.g,c.b);
        }
    }
}

