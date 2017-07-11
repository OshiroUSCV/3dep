#include "mat.h"

// Includes: DEBUG
#if defined _DEBUG
#include <stdio.h>
#endif

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