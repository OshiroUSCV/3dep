#pragma once
#ifndef __QUAT_H__
#define __QUAT_H__

#include "vec.h"

class Quaternion
{
protected:
	float m_valReal;		// Coefficient (real)
	vec3f m_vecPure;	// Coefficients (imaginary)

public:
	Quaternion(float i = 0.0f, float j = 0.0f, float k = 0.0f, float w = 0.0f);
	Quaternion(vec3f valsImaginary, float valReal);
	Quaternion(vec4f v);

	// Accessors
//	float operator[](int idx) const;
//	float& operator[](int idx);

	vec3f& GetImaginaryVector();
	vec3f GetImaginaryVector() const;

	float& i()
	{
		return m_vecPure[0];
	}

	float i() const
	{
		return m_vecPure[0];
	}

	float& j()
	{
		return m_vecPure[1];
	}

	float j() const
	{
		return m_vecPure[1];
	}

	float& k()
	{
		return m_vecPure[2];
	}

	float k() const
	{
		return m_vecPure[2];
	}

	float& w()
	{
		return m_valReal;
	}

	float w() const
	{
		return m_valReal;
	}

	bool IsPure() const
	{
		return (-0.00001f <= m_valReal && m_valReal <= 0.00001f); // :TODO: Figure out a good error buffer value & #define it
	}

	float GetNorm() const;
	Quaternion GetConjugate() const;
	Quaternion GetInverse() const;

	void Normalize();

	static vec3f RotateVectorR(vec3f vecInitial, vec3f vecRot, float angleRadians);
	static vec3f RotateVectorD(vec3f vecInitial, vec3f vecRot, float angleDegrees);
};

Quaternion operator*(float fScalar, Quaternion q);
Quaternion operator*(Quaternion q1, Quaternion q2);

Quaternion operator*(Quaternion q, vec3f v);
Quaternion operator*(vec3f v, Quaternion q);

#endif	// #ifndef __QUAT_H__