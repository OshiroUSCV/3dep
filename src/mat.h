#ifndef __MAT_H__
#define __MAT_H__

#define _USE_MATH_DEFINES
#include <math.h>
#include "vec.h"

#define MAT_ROWS	// Matrix is row-major in the sense that it consists of an array of row vectors

//////////////////////////////////////////////////////////
// CLASS: mat33
// DESCR: 3x3 matrix

class mat33
{
protected:
	vec3f m_rows[3];

public:
	// Setup & Initialization
	mat33(vec3f r0 = vec3f(), vec3f r1 = vec3f(), vec3f r2 = vec3f());

	// Accessor: Row
	vec3f operator[](int idx) const;
	vec3f& operator[](int idx);
	// Accessor: Col
	vec3f GetColumn(int idx) const;

	mat33 GetTranspose() const;
	float GetDeterminant() const;

	// DEBUG
	void Print() const;
};

// mat33: Operator Overloads
mat33 operator+(const mat33 m1, const mat33 m2);
mat33 operator-(const mat33 m1, const mat33 m2);
mat33 operator*(const float fScalar, const mat33 mat);

// 3x3 matrix  * column vec3 = column vec3
vec3f operator*(const mat33 m1, const vec3f v1);
// 3x3 matrix  * 3x3 matrix = 3x3 matrix
mat33 operator*(const mat33 m1, const mat33 m2);

const mat33 MAT33_IDENTITY
(
	vec3f(1.0f, 0.0f, 0.0f),
	vec3f(0.0f, 1.0f, 0.0f),
	vec3f(0.0f, 0.0f, 1.0f)
	);

//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// CLASS: mat44
// DESCR: 4x4 matrix

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

	// 
	mat44 GetTranspose() const;
	mat33 GetMinor(int row, int col) const;
	mat44 GetCofactorsMatrix() const;
	float GetDeterminant() const;
	bool TryGetInverse(mat44& rMatResult) const;

	// 3D Manipulation
	static mat44 GetMatrixRotXD(float fRotXDegrees);
	static mat44 GetMatrixRotYD(float fRotYDegrees);
	static mat44 GetMatrixRotZD(float fRotZDegrees);
	static mat44 GetMatrixScale(float fScale);

	// DEBUG
	void Print() const;

};

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
//////////////////////////////////////////////////////////


#endif // #ifndef __MAT_H__