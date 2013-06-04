/* Defines interface for a vector. */

#ifndef VECTOR
#define VECTOR

	#include <iostream>

	using namespace std;

	/* Forward declaration of Matrix class. */
	class Matrix;


	/* A 4x1 vector containing a double in each entry. The vector entries are indexed by i,
	   which starts at 0 and increases as the vector goes down. The vectors entries are thus
	   indexed as such:

	 i  [v00]
	 |  [v10]
	 |  [v20]
	 V  [v30]

	*/
	class Vector {


		/* Friend functions: */

		/* Performs scalar multiplication with V and returns a new vector. Scalar multiplication is commutative. */
		friend Vector operator* (const Vector& v, double value);
		friend Vector operator* (double value, const Vector& v);

		/* Performs scalar division with V and returns a new vector. Scalar division is commutative. */
		friend Vector operator/ (const Vector& v, double value);
		friend Vector operator/ (double value, const Vector& v);

		/* Returns true if the entries of V1 are the same as the entries of V2, false otherwise. */
		friend bool operator== (const Vector& v1, const Vector& v2);

		/* Returns true if the entries of V1 aren't exactly the same as the entries of V2, false otherwise. */
		friend bool operator!= (const Vector& v1, const Vector& v2);

		/* Performs matrix/vector multiplication by multiplying M with V and returns a new vector. */
		friend Vector operator* (const Matrix& m, const Vector& v); // Defined in Matrix.cpp.


		private:
			/* Each of the entries in the vector. */
			double entries [4];


		public:
			/* Default contructor. Initializes a 4x1 vector with zeroes for all entries. */
			Vector ();

			/* Constructor that initializes vector entries with the supplied values. */
			Vector (double value0, double value1, double value2, double value3);


			/* Performs vector addition with V and returns a new vector. */
			Vector operator+ (const Vector &v) const;

			/* Performs vector addition with V in place and returns a reference to this vector. Modifies this vector. */
			Vector& operator+= (const Vector &v);

			/* Performs vector subtraction with V and returns a new vector. */
			Vector operator- (const Vector &v) const;

			/* Performs vector subtraction with V in place and returns a reference to this vector. Modifies this vector. */
			Vector& operator-= (const Vector &v);

			/* Performs scalar multiplication with V in place and returns a reference to this vector. Modifies this vector. */
			Vector& operator*= (double value);

			/* Performs scalar division with V in place and returns a reference to this vector. Modifies this vector. */
			Vector& operator/= (double value);

			/* Returns a reference to entry at i where i = row #. WARNING: Aborts program if i is out-of-bounds! */
			double& operator[] (int i);


			/* Returns the dot product of this vector with V. */
			double dotProduct (const Vector &v) const;

			/* Treats both this vector and V as 3x1 vectors and computes the cross product. The last entry of this
			   vector will be the last entry of the return vector. */
			Vector crossProduct (const Vector &v) const;

			/* Returns the distance between this vector and V, assuming both vectors are fixed in space. */
			double distance (const Vector &v) const;

			/* Returns the magnitude of this vector. */
			double magnitude (void) const;

			/* Normalizes this vector in place to an unit vector and returns a reference to this vector. Modifies this vector. */
			Vector& normalize (void);


			/* Sets entry at i to VALUE where i = row #. WARNING: Aborts program if i is out-of-bounds! */
			void setEntry (int i, double value);

			/* Gets value of entry at i where i = row #. WARNING: Aborts program if i is out-of-bounds! */
			double getEntry (int i) const;


			/* Print member function. */
			void print (ostream *os) const;

	};

	/* Printing operator for Vector class. */
	ostream& operator<< (ostream &os, const Vector &v);

#endif