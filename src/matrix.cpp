/* Contains method definitions and related functions for a matrix. 
   Check matrix.h for documentation on what each function does. */

#include <iostream>
#include <cstdio>
#include <cassert>

#include "vector.h"
#include "matrix.h"


using namespace std;


/**********************************
  Matrix class member functions: 
***********************************/


/* Default contructor. Initializes a 4x4 matrix with zeroes for all entries. */
Matrix::Matrix () {
	m00 = 0; m01 = 0; m02 = 0; m03 = 0;
	m10 = 0; m11 = 0; m12 = 0; m13 = 0;
	m20 = 0; m21 = 0; m22 = 0; m23 = 0;
	m30 = 0; m31 = 0; m32 = 0; m33 = 0;

	/* Initialize elements of entry pointer array. */

	/* Row 1. */
	entryPointers[0] = &m00; 
	entryPointers[1] = &m01; 
	entryPointers[2] = &m02; 
	entryPointers[3] = &m03;

	/* Row 2. */
	entryPointers[4] = &m10,
	entryPointers[5] = &m11; 
	entryPointers[6] = &m12; 
	entryPointers[7] = &m13;

	/* Row 3. */
	entryPointers[8] =  &m20,
	entryPointers[9] =  &m21; 
	entryPointers[10] = &m22; 
	entryPointers[11] = &m23;

	/* Row 4. */
	entryPointers[12] =	&m30;
	entryPointers[13] = &m31;
	entryPointers[14] = &m32;
	entryPointers[15] = &m33;
	
}



/* Constructor that initializes matrix entries with the supplied values. */
Matrix::Matrix ( double value00, double value01, double value02, double value03,
				 double value10, double value11, double value12, double value13,
				 double value20, double value21, double value22, double value23,
				 double value30, double value31, double value32, double value33 ) {

	m00 = value00; m01 = value01; m02 = value02; m03 = value03;
	m10 = value10; m11 = value11; m12 = value12; m13 = value13;
	m20 = value20; m21 = value21; m22 = value22; m23 = value23;
	m30 = value30; m31 = value31; m32 = value32; m33 = value33;

	/* Initialize elements of entry pointer array. */

	/* Row 1. */
	entryPointers[0] = &m00; 
	entryPointers[1] = &m01; 
	entryPointers[2] = &m02; 
	entryPointers[3] = &m03;

	/* Row 2. */
	entryPointers[4] = &m10,
	entryPointers[5] = &m11; 
	entryPointers[6] = &m12; 
	entryPointers[7] = &m13;

	/* Row 3. */
	entryPointers[8] =  &m20,
	entryPointers[9] =  &m21; 
	entryPointers[10] = &m22; 
	entryPointers[11] = &m23;

	/* Row 4. */
	entryPointers[12] =	&m30;
	entryPointers[13] = &m31;
	entryPointers[14] = &m32;
	entryPointers[15] = &m33;

}



/* Copy constructor. */
Matrix::Matrix (const Matrix &source) {
	*this = source;
}



/* Assignment operator. */
void Matrix::operator= (const Matrix &source) {

	/* If assigning matrix to itself, terminate early. Nothing to be done. */
	if (this == &source) {
		return;
	}

	/* Copy all entries to SOURCE. */
	m00 = source.m00; m01 = source.m01; m02 = source.m02; m03 = source.m03;
	m10 = source.m10; m11 = source.m11; m12 = source.m12; m13 = source.m13;
	m20 = source.m20; m21 = source.m21; m22 = source.m22; m23 = source.m23;
	m30 = source.m30; m31 = source.m31; m32 = source.m32; m33 = source.m33;


	/* Initialize elements of entry pointer array for newly assigned matrix. */

	/* Row 1. */
	entryPointers[0] = &m00; 
	entryPointers[1] = &m01; 
	entryPointers[2] = &m02; 
	entryPointers[3] = &m03;

	/* Row 2. */
	entryPointers[4] = &m10;
	entryPointers[5] = &m11; 
	entryPointers[6] = &m12; 
	entryPointers[7] = &m13;

	/* Row 3. */
	entryPointers[8] =  &m20;
	entryPointers[9] =  &m21; 
	entryPointers[10] = &m22; 
	entryPointers[11] = &m23;

	/* Row 4. */
	entryPointers[12] =	&m30;
	entryPointers[13] = &m31;
	entryPointers[14] = &m32;
	entryPointers[15] = &m33;

}



/* Performs matrix addition with M and returns a new matrix. */
Matrix Matrix::operator+ (const Matrix &m) const {
	return Matrix (
		m00+m.m00, m01+m.m01, m02+m.m02, m03+m.m03,
		m10+m.m10, m11+m.m11, m12+m.m12, m13+m.m13,
		m20+m.m20, m21+m.m21, m22+m.m22, m23+m.m23,
		m30+m.m30, m31+m.m31, m32+m.m32, m33+m.m33
	);
}



/* Performs matrix addition with M in place and returns a reference to this matrix. Modifies this matrix. */
Matrix& Matrix::operator+= (const Matrix &m) {
		m00+=m.m00; m01+=m.m01; m02+=m.m02; m03+=m.m03;
		m10+=m.m10; m11+=m.m11; m12+=m.m12; m13+=m.m13;
		m20+=m.m20; m21+=m.m21; m22+=m.m22; m23+=m.m23;
		m30+=m.m30; m31+=m.m31; m32+=m.m32; m33+=m.m33;
	return *this;
}



/* Performs matrix subtraction with M and returns a new matrix. */
Matrix Matrix::operator- (const Matrix &m) const {
	return Matrix (
		m00-m.m00, m01-m.m01, m02-m.m02, m03-m.m03,
		m10-m.m10, m11-m.m11, m12-m.m12, m13-m.m13,
		m20-m.m20, m21-m.m21, m22-m.m22, m23-m.m23,
		m30-m.m30, m31-m.m31, m32-m.m32, m33-m.m33
	);
}



/* Performs matrix subtraction with M in place and returns a reference to this matrix. Modifies this matrix. */
Matrix& Matrix::operator-= (const Matrix &m) {
	m00-=m.m00; m01-=m.m01; m02-=m.m02; m03-=m.m03;
	m10-=m.m10; m11-=m.m11; m12-=m.m12; m13-=m.m13;
	m20-=m.m20; m21-=m.m21; m22-=m.m22; m23-=m.m23;
	m30-=m.m30; m31-=m.m31; m32-=m.m32; m33-=m.m33;

	return *this;
}



/* Performs scalar multiplication with M in place and returns a reference to this matrix. Modifies this matrix. */
Matrix& Matrix::operator*= (double value) {
	m00*=value; m01*=value; m02*=value; m03*=value;
	m10*=value; m11*=value; m12*=value; m13*=value;
	m20*=value; m21*=value; m22*=value; m23*=value;
	m30*=value; m31*=value; m32*=value; m33*=value;

	return *this;
}



/* Performs matrix multiplication with M and returns a new matrix. Matrix multiplication IS NOT commutative. */
Matrix Matrix::operator* (const Matrix &m) const {
	return Matrix (
		/* Row 1 of resultant matrix. */
		m00*m.m00 + m01*m.m10 + m02*m.m20 + m03*m30, 
		m00*m.m01 + m01*m.m11 + m02*m.m21 + m03*m31,
		m00*m.m02 + m01*m.m12 + m02*m.m22 + m03*m32,
		m00*m.m03 + m01*m.m13 + m02*m.m23 + m03*m33,

		/* Row 2 of resultant matrix. */
		m10*m.m00 + m11*m.m10 + m12*m.m20 + m13*m30, 
		m10*m.m01 + m11*m.m11 + m12*m.m21 + m13*m31,
		m10*m.m02 + m11*m.m12 + m12*m.m22 + m13*m32,
		m10*m.m03 + m11*m.m13 + m12*m.m23 + m13*m33,

		/* Row 3 of resultant matrix. */
		m20*m.m00 + m21*m.m10 + m22*m.m20 + m23*m30, 
		m20*m.m01 + m21*m.m11 + m22*m.m21 + m23*m31,
		m20*m.m02 + m21*m.m12 + m22*m.m22 + m23*m32,
		m20*m.m03 + m21*m.m13 + m22*m.m23 + m23*m33,

		/* Row 4 of resultant matrix. */
		m30*m.m00 + m31*m.m10 + m32*m.m20 + m33*m30, 
		m30*m.m01 + m31*m.m11 + m32*m.m21 + m33*m31, 
		m30*m.m02 + m31*m.m12 + m32*m.m22 + m33*m32, 
		m30*m.m03 + m31*m.m13 + m32*m.m23 + m33*m33 
	);
}



/* Transposes the matrix in place and returns a reference to this matrix. Modifies this matrix. */
Matrix& Matrix::transpose (void) {
	double temp;

	temp = m10; m10 = m01; m01 = temp;
	temp = m20; m20 = m02; m02 = temp;
	temp = m30; m30 = m03; m03 = temp;
	temp = m21; m21 = m12; m12 = temp;
	temp = m31; m31 = m13; m13 = temp;
	temp = m32; m32 = m23; m23 = temp;

	return *this;
}



/* Sets entry at (i, j) to VALUE where i = row #, j = column #. WARNING: Aborts program if either i or j are out-of-bounds! */
void Matrix::setEntry (int i, int j, double value) {
	assert (i <= 3 && i >= 0); 
	assert (j <= 3 && j >= 0);

	/* Grab the corresponding memory location of the entry, then stick VALUE in that memory location. */
	int index = (i != 0) ? (4*i + j) : j; // Get index of matrix entry at (i, j).
	*entryPointers[index] = value;
}



/* Gets value of entry at (i, j) where i = row #, j = column #. WARNING: Aborts program if either i or j are out-of-bounds! */
double Matrix::getEntry (int i, int j) const {
	assert (i <= 3 && i >= 0); 
	assert (j <= 3 && j >= 0);

	/* Grab the corresponding memory location of the entry, then return the value at that memory location. */
	int index = (i != 0) ? (4*i + j) : j; // Get index of matrix entry at (i, j).
	return *entryPointers[index];
}



/* Print member function. */
void Matrix::print (ostream *os) const {
	printf("[%10f, %10f, %10f, %10f]\n[%10f, %10f, %10f, %10f]\n[%10f, %10f, %10f, %10f]\n[%10f, %10f, %10f, %10f]\n",
		m00, m01, m02, m03, 
		m10, m11, m12, m13, 
		m20, m21, m22, m23, 
		m30, m31, m32, m33);
}



/* Returns a 4x4 identity matrix. */
Matrix Matrix::getIdentity (void) {
	return Matrix( 
		1, 0, 0, 0,
		0, 1, 0, 0, 
		0, 0, 1, 0,
		0, 0, 0, 1 
	);
		
}



/******************* 
  Other functions:  
*********************/


/* Returns true if the entries of M1 are the same as the entries of M2, false otherwise. */
bool operator== (const Matrix& m1, const Matrix& m2) {
	return (m1.m00 == m2.m00) &&
	       (m1.m01 == m2.m01) &&
		   (m1.m02 == m2.m02) &&
		   (m1.m03 == m2.m03) &&

		   (m1.m10 == m2.m10) &&
	       (m1.m11 == m2.m11) &&
		   (m1.m12 == m2.m12) &&
		   (m1.m13 == m2.m13) &&

		   (m1.m20 == m2.m20) &&
	       (m1.m21 == m2.m21) &&
		   (m1.m22 == m2.m22) &&
		   (m1.m23 == m2.m23) &&

		   (m1.m30 == m2.m30) &&
	       (m1.m31 == m2.m31) &&
		   (m1.m32 == m2.m32) &&
		   (m1.m33 == m2.m33);
}



/* Returns true if the entries of M1 aren't exactly the same as the entries of M2, false otherwise. */
bool operator!= (const Matrix& m1, const Matrix& m2) {
	return (m1.m00 != m2.m00) ||
	       (m1.m01 != m2.m01) ||
		   (m1.m02 != m2.m02) ||
		   (m1.m03 != m2.m03) ||

		   (m1.m10 != m2.m10) ||
	       (m1.m11 != m2.m11) ||
		   (m1.m12 != m2.m12) ||
		   (m1.m13 != m2.m13) ||

		   (m1.m20 != m2.m20) ||
	       (m1.m21 != m2.m21) ||
		   (m1.m22 != m2.m22) ||
		   (m1.m23 != m2.m23) ||

		   (m1.m30 != m2.m30) ||
	       (m1.m31 != m2.m31) ||
		   (m1.m32 != m2.m32) ||
		   (m1.m33 != m2.m33);
}



/* Performs scalar multiplication with M and returns a new matrix. Scalar multiplication is commutative. */
Matrix operator* (const Matrix& m, double value) {
	return Matrix(
		m.m00*value, m.m01*value, m.m02*value, m.m03*value,
		m.m10*value, m.m11*value, m.m12*value, m.m13*value,
		m.m20*value, m.m21*value, m.m22*value, m.m23*value,
		m.m30*value, m.m31*value, m.m32*value, m.m33*value
	);
}



/* Performs scalar multiplication with M and returns a new matrix. Scalar multiplication is commutative. */
Matrix operator* (double value, const Matrix& m) {
	return Matrix(
		m.m00*value, m.m01*value, m.m02*value, m.m03*value,
		m.m10*value, m.m11*value, m.m12*value, m.m13*value,
		m.m20*value, m.m21*value, m.m22*value, m.m23*value,
		m.m30*value, m.m31*value, m.m32*value, m.m33*value
	);
}



/* Performs matrix/vector multiplication by multiplying M with V and returns a new vector. */
Vector operator* (const Matrix& m, const Vector& v) {
	return Vector(
		v.entries[0]*m.m00 + v.entries[1]*m.m01 + v.entries[2]*m.m02 + v.entries[3]*m.m03,
		v.entries[0]*m.m10 + v.entries[1]*m.m11 + v.entries[2]*m.m12 + v.entries[3]*m.m13,
		v.entries[0]*m.m20 + v.entries[1]*m.m21 + v.entries[2]*m.m22 + v.entries[3]*m.m23,
		v.entries[0]*m.m30 + v.entries[1]*m.m31 + v.entries[2]*m.m32 + v.entries[3]*m.m33
	);
}



/* Printing operator. */
ostream& operator<< (ostream &os, const Matrix &m) {
	m.print(&os);
	return os;
}


