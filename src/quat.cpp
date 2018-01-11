#include "quat.h"

Quaternion::Quaternion(float i /*= 0.0f*/, float j /*= 0.0f*/, float k /*= 0.0f*/, float w /*= 0.0f*/) :
	m_vecPure(i, j, k),
	m_valReal(w)
{
}

Quaternion::Quaternion(vec4f v) :
	Quaternion(v[0], v[1], v[2], v[3])
{
}

Quaternion::Quaternion(vec3f valsImaginary, float valReal) :
	Quaternion(valsImaginary[0], valsImaginary[1], valsImaginary[2], valReal)
{
}

vec3f& Quaternion::GetImaginaryVector()
{
	return m_vecPure;
}

vec3f Quaternion::GetImaginaryVector() const
{
	return m_vecPure;
}

//float Quaternion::operator[](int idx) const
//{
//	return m_vecPure[idx];
//}
//
//float& Quaternion::operator[](int idx)
//{
//	return m_vecPure[idx];
//}

float Quaternion::GetNorm() const
{
	return sqrt((m_valReal * m_valReal) + vec3f::DotProduct(m_vecPure, m_vecPure));
}

Quaternion Quaternion::GetConjugate() const
{
	return Quaternion(-1.0f * m_vecPure, m_valReal);
}

void Quaternion::Normalize()
{
	float f_norm = GetNorm();

	m_valReal /= f_norm;
	m_vecPure = (1.0f / f_norm) * m_vecPure;
}

Quaternion Quaternion::GetInverse() const
{
	return ((1.0f / pow(GetNorm(), 2)) * GetConjugate());
}


/**
*	Rotate a direction vector around a given vector by a given angle (degrees)
*	@param	vecInitial		Initial direction vector
*	@param	vecRot			Vector to rotate around
*	@param	angleRadians	How much to rotate around vecRot (radians)
*	@return direction		Rotated direction vector
**/
vec3f Quaternion::RotateVectorR(vec3f vecInitial, vec3f vecRot, float angleRadians)
{
	float cos_hrot = cos(angleRadians / 2.0f);
	float sin_hrot = sin(angleRadians / 2.0f);

	// Normalize vector
	vecRot.Normalize();

	// Construct rotation quaternions
	Quaternion q(sin_hrot * vecRot, cos_hrot);
	Quaternion q_inv(-sin_hrot * vecRot, cos_hrot);

	// Apply rotation
	Quaternion result = q * vecInitial;
	result = result * q_inv;
	return result.GetImaginaryVector();
}

/**
*	Rotate a direction vector around a given vector by a given angle (degrees)
*	@param	vecInitial		Initial direction vector
*	@param	vecRot			Vector to rotate around
*	@param	angleDegrees	How much to rotate around vecRot (degrees)
*	@return direction		Rotated direction vector
**/
vec3f Quaternion::RotateVectorD(vec3f vecInitial, vec3f vecRot, float angleDegrees)
{
	return RotateVectorR(vecInitial, vecRot, DegreesToRadians(angleDegrees));
}


Quaternion operator*(float fScalar, Quaternion q)
{
	return Quaternion(fScalar * q.i(), fScalar * q.j(), fScalar * q.k(), fScalar * q.w());
}

Quaternion operator*(Quaternion q1, Quaternion q2)
{
	Quaternion q_result;

	vec3f v1 = q1.GetImaginaryVector();
	vec3f v2 = q2.GetImaginaryVector();

	q_result.w()					= (q1.w() * q2.w()) - vec3f::DotProduct(v1, v2);
	q_result.GetImaginaryVector()	= (q1.w() * v2) + (q2.w() * v1) + vec3f::CrossProduct(v1, v2);

	return q_result;
}


Quaternion operator*(Quaternion q, vec3f v)
{
	return q * Quaternion(v, 0.0f);
}

Quaternion operator*(vec3f v, Quaternion q)
{
	return Quaternion(v, 0.0f) * q;
}

