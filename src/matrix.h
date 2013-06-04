/* Defines interface for a matrix. */

#ifndef MATRIX
#define MATRIX

	#include <iostream>

	using namespace std;

	/* Forward declaration of Vector class. */
	class Vector;


	/* A 4x4 matrix containing a double in each entry. The matrix is indexed ij, 
	where i represents the row and j represents the column. The top-left corner is indexed ij = 00, 
	and columns increase going right while rows increase going down. Thus, the matrix
	entries are indexed as such:          
	    j---->

	 i  [m00, m01, m02, m03]
	 |  [m10, m11, m12, m13]
	 |  [m20, m21, m22, m23]
	 V  [m30, m31, m32, m33]

	*/
	class Matrix {


		/* Friend functions: */

		/* Performs scalar multiplication with M and returns a new matrix. Scalar multiplication is commutative. */
		friend Matrix operator* (const Matrix& m, double value);
		friend Matrix operator* (double value, const Matrix& m);

		/* Returns true if the entries of M1 are the same as the entries of M2, false otherwise. */
		friend bool operator== (const Matrix& m1, const Matrix& m2);

		/* Returns true if the entries of M1 aren't exactly the same as the entries of M2, false otherwise. */
		friend bool operator!= (const Matrix& m1, const Matrix& m2);

		/* Performs matrix/vector multiplication by multiplying M with V and returns a new vector. */
		friend Vector operator* (const Matrix& m, const Vector& v);


		private:
			/* Each of the entries in the matrix. */
			double m00, m01, m02, m03,
				   m10, m11, m12, m13,
				   m20, m21, m22, m23,
				   m30, m31, m32, m33;

			/* An array of pointers to each of the entries in the array. This is used to more 
			   easily and cleanly access or change individuals elements in some methods. 
			   The elements are organized one row at a time, with the entry at row 0, column 0 
			   starting at element 0. 

				A matrix entry can be obtained by...   

					int index = (i != 0) ? (4*i + j) : j;
					*entryPointers[index];

				...where i is the row number and j is the column number.

			   */
			double* entryPointers [16];


		public:
			/* Default contructor. Initializes a 4x4 matrix with zeroes for all entries. */
			Matrix ();

			/* Constructor that initializes matrix entries with the supplied values. */
			Matrix ( double value00, double value01, double value02, double value03,
					 double value10, double value11, double value12, double value13,
					 double value20, double value21, double value22, double value23,
					 double value30, double value31, double value32, double value33 );

			/* Copy constructor. */
			Matrix (const Matrix &source);


			/* Assignment operator. */
			void operator= (const Matrix &source);


			/* Performs matrix addition with M and returns a new matrix. */
			Matrix operator+ (const Matrix &m) const;

			/* Performs matrix addition with M in place and returns a reference to this matrix. Modifies this matrix. */
			Matrix& operator+= (const Matrix &m);

			/* Performs matrix subtraction with M and returns a new matrix. */
			Matrix operator- (const Matrix &m) const;

			/* Performs matrix subtraction with M in place and returns a reference to this matrix. Modifies this matrix. */
			Matrix& operator-= (const Matrix &m);

			/* Performs scalar multiplication with M in place and returns a reference to this matrix. Modifies this matrix. */
			Matrix& operator*= (double value);

			/* Performs matrix multiplication with M and returns a new matrix. Matrix multiplication IS NOT commutative. */
			Matrix operator* (const Matrix &m) const;


			/* Transposes the matrix in place and returns a reference to this matrix. Modifies this matrix. */
			Matrix& transpose(void);

			/* Sets entry at (i, j) to VALUE where i = row #, j = column #. WARNING: Aborts program if either i or j are out-of-bounds! */
			void setEntry(int i, int j, double value);

			/* Gets value of entry at (i, j) where i = row #, j = column #. WARNING: Aborts program if either i or j are out-of-bounds! */
			double getEntry(int i, int j) const;


			/* Print member function. */
			void print (ostream *os) const;


			/* Returns a 4x4 identity matrix. */
			static Matrix getIdentity(void);

	};

	/* Printing operator for Matrix class. */
	ostream& operator<< (ostream &os, const Matrix &m);

#endif