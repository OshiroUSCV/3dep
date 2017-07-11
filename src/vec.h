#ifndef __VEC_H__
#define __VEC_H__

// Includes: Standard
#include <math.h>


//#define __TEMPLATE_VEC__
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
		return val_dp;
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
	float mf_x;
	float mf_y;

public:
	// Setup & Initialization
	vec2f();
	vec2f(float x, float y);

	// Getter/Setters
	float& x()
	{
		return mf_x;
	}

	float x() const
	{
		return mf_x;
	}

	float& y()
	{
		return mf_y;
	}

	float y() const
	{
		return mf_y;
	}

	// Maths
	static float DotProduct(const vec2f v1, const vec2f v2);
	float GetNorm() const;
	void Normalize();

	///////////////////////
	// DEBUG
	void Print();
};
// vec2f: Operator Overloads
vec2f operator+(const vec2f v1, const vec2f v2);
vec2f operator-(const vec2f v1, const vec2f v2);
vec2f operator*(const float fScalar, const vec2f vec);

class vec3f
{
protected:
	// Properties
	float m_vec[3];

public:
	// Setup & Initialization
	vec3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);

	// Getter/Setters
	float operator[](int idx) const;
	float& operator[](int idx);

	float& x()
	{
		return m_vec[0];
	}

	float x() const
	{
		return m_vec[0];
	}

	float& y()
	{
		return m_vec[1];
	}

	float y() const
	{
		return m_vec[1];
	}

	float& z()
	{
		return m_vec[2];
	}

	float z() const
	{
		return m_vec[2];
	}

	// Maths
	static float DotProduct(const vec3f v1, const vec3f v2);
	static vec3f CrossProduct(const vec3f v1, const vec3f v2);
	float GetNorm() const;
	void Normalize();

	///////////////////////
	// DEBUG
	void Print();
};

// vec3f: Operator Overloads
vec3f operator+(const vec3f v1, const vec3f v2);
vec3f operator-(const vec3f v1, const vec3f v2);
vec3f operator*(const float fScalar, const vec3f vec);

class vec4f
{
protected:
	// Properties
	float m_vec[4];

public:
	// Setup & Initialization
	vec4f(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

	// Getter/Setters
	float operator[](int idx) const;
	float& operator[](int idx);

	float& x()
	{
		return m_vec[0];
	}

	float x() const
	{
		return m_vec[0];
	}

	float& y()
	{
		return m_vec[1];
	}

	float y() const
	{
		return m_vec[1];
	}

	float& z()
	{
		return m_vec[2];
	}

	float z() const
	{
		return m_vec[2];
	}

	float& w()
	{
		return m_vec[3];
	}

	float w() const
	{
		return m_vec[3];
	}

	// Maths
	static float DotProduct(const vec4f v1, const vec4f v2);
	//static vec3f CrossProduct(const vec3f v1, const vec3f v2);
	float GetNorm() const;
	void Normalize();

	///////////////////////
	// DEBUG
	void Print();
};

// vec4f: Operator Overloads
vec4f operator+(const vec4f v1, const vec4f v2);
vec4f operator-(const vec4f v1, const vec4f v2);
vec4f operator*(const float fScalar, const vec4f vec);
#endif

#endif // #ifndef __VEC_H__