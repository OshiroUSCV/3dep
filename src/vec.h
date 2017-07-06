// Includes: Standard
#include <math.h>

// Includes: DEBUG
#if defined _DEBUG
	#include <stdio.h>
#endif

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