#ifndef __MAT_H__
#define __MAT_H__

#include "vec.h"

#define MAT_ROWS	// Matrix is row-major in the sense that it consists of an array of row vectors
#if defined MAT_ROWS

class mat44
{
protected:
	vec4f m_rows[4];

public:
	// Setup & Initialization
	mat44(vec4f r0 = vec4f(), vec4f r1 = vec4f(), vec4f r2 = vec4f(), vec4f r3 = vec4f());

	// Accessor: Row
	vec4f operator[](int idx) const;
	vec4f& operator[](int idx);
	// Accessor: Col
	vec4f GetColumn(int idx) const;

	// DEBUG
	void Print() const;

};

#else

class mat44
{
	vec4f m_cols[4];

	mat44(vec4f c0 = vec4f(), vec4f c1 = vec4f(), vec4f c2 = vec4f(), vec4f c3 = vec4f());

};
#endif
// mat44: Operator Overloads
mat44 operator+(const mat44 m1, const mat44 m2);
mat44 operator-(const mat44 m1, const mat44 m2);
mat44 operator*(const float fScalar, const mat44 mat);


// 4x4 matrix  * column vec4 = column vec4
vec4f operator*(const mat44 m1, const vec4f v1);

// 4x4 matrix  * 4x4 matrix = 4x4 matrix
mat44 operator*(const mat44 m1, const mat44 m2);

const mat44 MAT44_IDENTITY
	(
		vec4f(1.0f, 0.0f, 0.0f, 0.0f),
		vec4f(0.0f, 1.0f, 0.0f, 0.0f),
		vec4f(0.0f, 0.0f,1.0f, 0.0f),
		vec4f(0.0f, 0.0f, 0.0f,1.0f)
	);

#endif // #ifndef __MAT_H__