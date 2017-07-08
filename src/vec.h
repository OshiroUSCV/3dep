// Includes: Standard
#include <math.h>

// Includes: DEBUG
#if defined _DEBUG
	#include <stdio.h>
#endif

#define __TEMPLATE_VEC__
#if defined __TEMPLATE_VEC__

template <class T, unsigned vecSize>
class vec
{
protected:
	T m_vec[vecSize];

public:
	// Setup & Initialization
	vec(...)
	{

	}
	vec();

	// Maths
	static T DotProduct(const vec<T,vecSize> v1, const vec<T,vecSize> v2)
	{
		int val_dp = 0;
		for (int i = 0; i < vecSize; i++)
		{
			val_dp += (v1.m_vec[i] * v2.m_vec[i]);
		}
		return dp;
	}

	T GetNorm() const
	{
		return sqrt(DotProduct(*this, *this)));
	}

	void Normalize()
	{
		T vec_norm = GetNorm();
		for (int i = 0; i < vecSize; i++)
		{
			m_vec[i] /= vec_norm;
		}
	}
/*
public:
	
	vec2f();
	vec2f(float x, float y);

	// Getter/Setters
	float& x()
	{
		return m_x;
	}

	float x() const
	{
		return m_x;
	}

	void Normalize()
	{
		float vec_norm = GetNorm();
		m_x /= vec_norm;
		m_y /= vec_norm;
	}

	// Add
	vec2f operator+(const vec2f v2) const
	{
		return vec2f(m_x + v2.m_x, m_y + v2.m_y);
	}
	// Subtract
	vec2f operator-(const vec2f v2) const
	{
		return vec2f(m_x - v2.m_x, m_y - v2.m_y);
	}
	// Multiply (scalar)
	vec2f operator*(const float fScalar) const
	{
		return vec2f(fScalar * m_x, fScalar * m_y);
	}

#if defined _DEBUG
	// DEBUG
	void Print()
	{
		printf("(%f, %f)\n", m_x, m_y);
	}
#endif
	*/
};

typedef vec<float, 2> vec2f;
typedef vec<float, 3> vec3f;
typedef vec<float, 4> vec4f;

#else
class vec2f
{
protected:
	// Properties
	float m_x;
	float m_y;

public:
	// Setup & Initialization
	vec2f();
	vec2f(float x, float y);

	// Getter/Setters
	float& x()
	{
		return m_x;
	}

	float x() const
	{
		return m_x;
	}

	// Maths
	static float DotProduct(const vec2f v1, const vec2f v2)
	{
		return (v1.m_x * v2.m_x + v1.m_y * v2.m_y);
	}

	float GetNorm() const
	{
		return sqrt(m_x * m_x + m_y * m_y);
	}

	void Normalize()
	{
		float vec_norm = GetNorm();
		m_x /= vec_norm;
		m_y /= vec_norm;
	}

	// Add
	vec2f operator+(const vec2f v2) const
	{
		return vec2f(m_x + v2.m_x, m_y + v2.m_y);
	}
	// Subtract
	vec2f operator-(const vec2f v2) const
	{
		return vec2f(m_x - v2.m_x, m_y - v2.m_y);
	}
	// Multiply (scalar)
	vec2f operator*(const float fScalar) const
	{
		return vec2f(fScalar * m_x, fScalar * m_y);
	}

#if defined _DEBUG
	// DEBUG
	void Print()
	{
		printf("(%f, %f)\n", m_x, m_y);
	}
#endif
};

class vec3f
{

};

class vec4f
{

};
#endif