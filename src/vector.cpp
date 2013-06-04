/* Contains method definitions and related functions for a vector. 
   Check vector.h for documentation on what each function does. */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cassert>

#include "vector.h"

using namespace std;


/**********************************
  Vector class member functions: 
***********************************/


/* Default contructor. Initializes a 4x1 vector with zeroes for all entries. */
Vector::Vector () {
	entries[0] = 0;
	entries[1] = 0;
	entries[2] = 0;
	entries[3] = 0;
}



/* Constructor that initializes vector entries with the supplied values. */
Vector::Vector (double value0, double value1, double value2, double value3) {
	entries[0] = value0;
	entries[1] = value1;
	entries[2] = value2;
	entries[3] = value3;
}



/* Performs vector addition with V and returns a new vector. */
Vector Vector::operator+ (const Vector &v) const {
	return Vector(
		entries[0] + v.entries[0],
		entries[1] + v.entries[1],
		entries[2] + v.entries[2],
		entries[3] + v.entries[3]
	);
}



/* Performs vector addition with V in place and returns a reference to this vector. Modifies this vector. */
Vector& Vector::operator+= (const Vector &v) {
	entries[0] += v.entries[0];
	entries[1] += v.entries[1];
	entries[2] += v.entries[2];
	entries[3] += v.entries[3];

	return *this;
}



/* Performs vector subtraction with V and returns a new vector. */
Vector Vector::operator- (const Vector &v) const {
	return Vector(
		entries[0] - v.entries[0],
		entries[1] - v.entries[1],
		entries[2] - v.entries[2],
		entries[3] - v.entries[3]
	);
}



/* Performs vector subtraction with V in place and returns a reference to this vector. Modifies this vector. */
Vector& Vector::operator-= (const Vector &v) {
	entries[0] -= v.entries[0];
	entries[1] -= v.entries[1];
	entries[2] -= v.entries[2];
	entries[3] -= v.entries[3];

	return *this;
}



/* Performs scalar multiplication with V in place and returns a reference to this vector. Modifies this vector. */
Vector& Vector::operator*= (double value) {
	entries[0] *= value;
	entries[1] *= value;
	entries[2] *= value;
	entries[3] *= value;

	return *this;
}



/* Performs scalar division with V in place and returns a reference to this vector. Modifies this vector. */
Vector& Vector::operator/= (double value) {
	entries[0] /= value;
	entries[1] /= value;
	entries[2] /= value;
	entries[3] /= value;

	return *this;
}



/* Returns a reference to entry at i where i = row #. WARNING: Aborts program if i is out-of-bounds! */
double& Vector::operator[] (int i) {
	assert(i >= 0 && i <= 3);
	return entries[i];
}



/* Returns the dot product of this vector with V. */
double Vector::dotProduct (const Vector &v) const {
	double sum = 0.0;
	for (int i = 0; i < 4; i++) {
		sum += entries[i] * v.entries[i];
	}
	return sum;
}



/* Treats both this vector and V as 3x1 vectors and computes the cross product. The last entry of this
   vector will be the last entry of the return vector. */
Vector Vector::crossProduct (const Vector &v) const {
	return Vector(entries[1]*v.entries[2] - entries[2]*v.entries[1], 
				  entries[2]*v.entries[0] - entries[0]*v.entries[2], 
		          entries[0]*v.entries[1] - entries[1]*v.entries[0], 
		          entries[3]);
}



/* Returns the distance between this vector and V, assuming both vectors are fixed in space. */
double Vector::distance (const Vector &v) const {
	double sum = 0.0;
	for (int i = 0; i < 4; i++) {
		sum += ((entries[i]-v.entries[i]) * (entries[i]-v.entries[i]));
	}
	return sqrt(sum);
}



/* Returns the magnitude of this vector. */
double Vector::magnitude (void) const {

	double sum = 0.0;
	double component = 0.0;

	/* Sum up squared components of vector. */
	for (int i = 0; i < 4; i++) {
		component = entries[i];
		sum += component * component;
	}

	return sqrt(sum);
}



/* Normalizes this vector in place and returns a reference to this vector. Modifies this vector. */
Vector& Vector::normalize (void) {

	double magnitude = this->magnitude();

	/* If the zero vector, then terminate early. Normalization doesn't really make sense, so leave vector unchanged. */
	if (magnitude == 0) {
		return *this;
	}

	/* Divide each component of the vector by vector's magnitude. */
	for (int i = 0; i < 4; i++) {
		entries[i] /= magnitude;
	}

	return *this;
}



/* Sets entry at i to VALUE where i = row #. WARNING: Aborts program if i is out-of-bounds! */
void Vector::setEntry(int i, double value) {
	assert(i >= 0 && i <= 3);
	entries[i] = value;
}



/* Gets value of entry at i where i = row #. WARNING: Aborts program if i is out-of-bounds! */
double Vector::getEntry(int i) const {
	assert(i >= 0 && i <= 3);
	return entries[i];
}



/* Print member function. */
void Vector::print (ostream *os) const {
	printf("[Vector: %5.3f, %5.3f, %5.3f, %5.3f]", entries[0], entries[1], entries[2], entries[3]);
}


/******************* 
  Other functions:  
*********************/


/* Performs scalar multiplication with V and returns a new vector. Scalar multiplication is commutative. */
Vector operator* (const Vector& v, double value) {
	return Vector (
		v.entries[0] * value,
		v.entries[1] * value,
		v.entries[2] * value,
		v.entries[3] * value
	);
}



/* Performs scalar multiplication with V and returns a new vector. Scalar multiplication is commutative. */
Vector operator* (double value, const Vector& v) {
	return Vector (
		v.entries[0] * value,
		v.entries[1] * value,
		v.entries[2] * value,
		v.entries[3] * value
	);
}



/* Performs scalar division with V and returns a new vector. Scalar division is commutative. */
Vector operator/ (const Vector& v, double value) {
	return Vector (
		v.entries[0] / value,
		v.entries[1] / value,
		v.entries[2] / value,
		v.entries[3] / value
	);
}



/* Performs scalar division with V and returns a new vector. Scalar division is commutative. */
Vector operator/ (double value, const Vector& v) {
	return Vector (
		v.entries[0] / value,
		v.entries[1] / value,
		v.entries[2] / value,
		v.entries[3] / value
	);
}



/* Returns true if the entries of V1 are the same as the entries of V2, false otherwise. */
bool operator== (const Vector& v1, const Vector& v2) {
	return (v1.entries[0] == v2.entries[0]) &&
		   (v1.entries[1] == v2.entries[1]) &&
		   (v1.entries[2] == v2.entries[2]) &&
		   (v1.entries[3] == v2.entries[3]);
}



/* Returns true if the entries of V1 aren't exactly the same as the entries of V2, false otherwise. */
bool operator!= (const Vector& v1, const Vector& v2) {
	return (v1.entries[0] != v2.entries[0]) ||
		   (v1.entries[1] != v2.entries[1]) ||
		   (v1.entries[2] != v2.entries[2]) ||
		   (v1.entries[3] != v2.entries[3]);
}



/* Printing operator. */
ostream& operator<< (ostream &os, const Vector &v) {
	v.print(&os);
	return os;
}







