#include "mat.h"

// Includes: DEBUG
#if defined _DEBUG
#include <stdio.h>
#endif

//////////////////////////////////////////////////////////
// CLASS: mat33
// DESCR: 3x3 matrix
//////////////////////////////////////////////////////////

mat33::mat33(vec3f r0 /*= vec3f()*/, vec3f r1 /*= vec3f()*/, vec3f r2 /*= vec3f()*/) :
	m_rows{ r0,r1,r2 }
{
}

vec3f mat33::operator[](int idx) const
{
	return m_rows[idx];
}

vec3f& mat33::operator[](int idx)
{
	return m_rows[idx];
}

vec3f mat33::GetColumn(int idx) const
{
	vec3f vec_col;
	for (int i = 0; i < 3; i++)
	{
		vec_col[i] = m_rows[i][idx];
	}
	return vec_col;
}

// Operator+: mat33 + mat33
mat33 operator+(const mat33 m1, const mat33 m2)
{
	return mat33(m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2]);
}

// Operator-: mat33 - mat33
mat33 operator-(const mat33 m1, const mat33 m2)
{
	return mat33(m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2]);
}

// Operator*: fScalar * mat33
mat33 operator*(const float fScalar, const mat33 mat)
{
	return mat33(fScalar * mat[0], fScalar * mat[1], fScalar * mat[2]);
}

// Operator*: 3x3 matrix  * column vec3 = column vec3
vec3f operator*(const mat33 m1, const vec3f v1)
{
	return vec3f
		(
			vec3f::DotProduct(v1, m1[0]),
			vec3f::DotProduct(v1, m1[1]),
			vec3f::DotProduct(v1, m1[2])
			);
}

mat33 operator*(const mat33 m1, const mat33 m2)
{
	mat33 mat_result;

	// Column-first so we only have to construct the column vectors 4 times
	for (int c = 0; c < 4; c++)
	{
		vec3f col_curr = m2.GetColumn(c);

		for (int r = 0; r < 4; r++)
		{
			mat_result[r][c] = vec3f::DotProduct(m1[r], col_curr);
		}
	}

	return mat_result;
}

void mat33::Print() const
{
	printf("==================================\n");
	for (int r = 0; r < 3; r++)
	{
		printf("|%5f %5f %5f|\n", m_rows[r][0], m_rows[r][1], m_rows[r][2]);
	}
	printf("==================================\n");
}

//////////////////////////////////////////////////////////
// CLASS: mat44
// DESCR: 4x4 matrix
//////////////////////////////////////////////////////////

#if defined MAT_ROWS
mat44::mat44(vec4f r0 /*= vec4f()*/, vec4f r1 /*= vec4f()*/, vec4f r2 /*= vec4f()*/, vec4f r3 /*= vec4f()*/) :
	m_rows{ r0,r1,r2,r3 }
{
}

vec4f mat44::operator[](int idx) const
{
	return m_rows[idx];
}

vec4f& mat44::operator[](int idx)
{
	return m_rows[idx];
}

vec4f mat44::GetColumn(int idx) const
{
	vec4f vec_col;
	for (int i = 0; i < 4; i++)
	{
		vec_col[i] = m_rows[i][idx];
	}
	return vec_col;
}


// Retrieve minor matrix for specified indices (drop the row & column specified)
mat33 mat44::GetMinor(int row, int col)
{
	mat33 minor_mat;

	int minor_r = 0;
	for (int r = 0; r < 4; r++)
	{
		// Skip to next iteration if we're in a cut row
		if (r == row)
		{
			continue;
		}

		int minor_c = 0;
		for (int c = 0; c < 4; c++)
		{
			// Skip to next iteration if we're in a cut col
			if (c == col)
			{
				continue;
			}
			minor_mat[minor_r][minor_c] = m_rows[r][c];
			minor_c++;
		}
		minor_r++;
	}

	return minor_mat;
}

// Operator+: mat44 + mat44
mat44 operator+(const mat44 m1, const mat44 m2)
{
	return mat44(m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3]);
}

// Operator-: mat44 - mat44
mat44 operator-(const mat44 m1, const mat44 m2)
{
	return mat44(m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2], m1[3] - m2[3]);
}

// Operator*: fScalar * mat44
mat44 operator*(const float fScalar, const mat44 mat)
{
	return mat44(fScalar * mat[0], fScalar * mat[1], fScalar * mat[2], fScalar * mat[3]);
}

// Operator*: 4x4 matrix  * column vec4 = column vec4
vec4f operator*(const mat44 m1, const vec4f v1)
{
	return vec4f
	(
		vec4f::DotProduct(v1, m1[0]),
		vec4f::DotProduct(v1, m1[1]),
		vec4f::DotProduct(v1, m1[2]),
		vec4f::DotProduct(v1, m1[3])
	);
}

mat44 operator*(const mat44 m1, const mat44 m2)
{
	mat44 mat_result;

	// Column-first so we only have to construct the column vectors 4 times
	for (int c = 0; c < 4; c++)
	{
		vec4f col_curr = m2.GetColumn(c);

		for (int r = 0; r < 4; r++)
		{
			mat_result[r][c] = vec4f::DotProduct(m1[r], col_curr);
		}
	}

	return mat_result;
}

void mat44::Print() const
{
	printf("==================================\n");
	for (int r = 0; r < 4; r++)
	{
		printf("|%5f %5f %5f %5f|\n", m_rows[r][0], m_rows[r][1], m_rows[r][2], m_rows[r][3]);
	}
	printf("==================================\n");
}

#else	// MAT_COLS
mat44::mat44(vec4f c0 /*= vec4f()*/, vec4f c1 /*= vec4f()*/ , vec4f c2 /*= vec4f()*/ , vec4f c3 /*= vec4f()*/ ) :
	m_cols{ c0,c1,c2,c3 }
{
}
#endif