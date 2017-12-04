#include "vec.h"

// Includes: DEBUG
#if defined _DEBUG
#include <stdio.h>
#endif


////////////////////
// CLASS: vec2f
////////////////////

// Setup & Initialization
vec2f::vec2f(float x, float y) :
	mf_x(x),
	mf_y(y)
{
}

vec2f::vec2f() : vec2f(0.0f, 0.0f)
{
}

// Maths
float vec2f::DotProduct(const vec2f v1, const vec2f v2)
{
	return (v1.mf_x * v2.mf_x + v1.mf_y * v2.mf_y);
}

float vec2f::GetNorm() const
{
	return sqrt(mf_x * mf_x + mf_y * mf_y);
}

void vec2f::Normalize()
{
	float vec_norm = GetNorm();
	mf_x /= vec_norm;
	mf_y /= vec_norm;
}

// Add
vec2f operator+(const vec2f v1, const vec2f v2)
{
	return vec2f(v1.x() + v2.x(), v1.y() + v2.y());
}
// Subtract
vec2f operator-(const vec2f v1, const vec2f v2)
{
	return vec2f(v1.x() - v2.x(), v1.y() - v2.y());
}

vec2f operator*(const float fScalar, const vec2f vec)
{
	return vec2f(fScalar * vec.x(), fScalar * vec.y());
}

// DEBUG
void vec2f::Print()
{
#if defined _DEBUG
	printf("(%f, %f)\n", mf_x, mf_y);
#endif
}


////////////////////
// CLASS: vec3f
////////////////////

// Setup & Initialization
vec3f::vec3f(float x /*= 0.0f*/, float y /*= 0.0f*/, float z /*= 0.0f*/) :
	m_vec{ x,y,z }
{
}

// Accessor
float vec3f::operator[](int idx) const
{
	return m_vec[idx];
}

float& vec3f::operator[](int idx)
{
	return m_vec[idx];
}

float vec3f::DotProduct(const vec3f v1, const vec3f v2)
{
	float val_dp = 0;
	for (int i = 0; i < 3; i++)
	{
		val_dp += (v1[i] * v2[i]);
	}
	return val_dp;
}

vec3f vec3f::CrossProduct(const vec3f v1, const vec3f v2)
{
	return vec3f
	(
		(v1.y() * v2.z()) - (v1.z() * v2.y()),
		(v1.z() * v2.x()) - (v1.x() * v2.z()),
		(v1.x() * v2.y()) - (v1.y() * v2.x())
	);
}

float vec3f::GetNorm() const
{
	return sqrt(DotProduct(*this, *this));
}
void vec3f::Normalize()
{
	float vec_norm = GetNorm();	// :NOTE: Not verifying that our magnitude is > 0
	for (int i = 0; i < 3; i++)
	{
		m_vec[i] /= vec_norm;
	}
}

// Operator Overload: Add
vec3f operator+(const vec3f v1, const vec3f v2)
{
	return vec3f(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}
// Operator Overload: Subtract
vec3f operator-(const vec3f v1, const vec3f v2)
{
	return vec3f(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

// Operator Overload: Scalar Multiplication
vec3f operator*(const float fScalar, const vec3f vec)
{
	return vec3f(fScalar * vec.x(), fScalar * vec.y(), fScalar * vec.z());
}

/**
 *	Calculate directional vector for a missile moving at a given speed
 *	to intercept a target given a constant velocity vector for the target
 *
 *	@param	posMsl		Initial position of the missile
 *	@param	fSpeedMsl	Speed of the missile (constant)
 *	@param	posTarget	Initial position of the target
 *	@param	velTarget	Velocity vector of target
 *	@return	Unit vector pointing in the direction to intercept target (or along same vector as target, if cannot intercept)
 */
vec3f GetTargetIntercept(vec3f posMsl, float fSpeedMsl, vec3f posTarget, vec3f velTarget)
{
	// First, calculate vector from missile to target
	vec3f vec_m2t	= posTarget - posMsl;
	// Convert to unit vector
	vec3f uvec_m2t	= (1.0f / vec_m2t.GetNorm()) * vec_m2t;
	// Also, calculate the target velocity's magnitude for later
	float mag_vt	= velTarget.GetNorm();

	///////////////////////////
	// Next, project the target velocity onto the m2t vector to determine parallel (p) & orthogonal (o) component vectors
	vec3f vel_target_o, vel_target_p;

	// Start by calculating the dot product between our target velocity vector and the m2t vector
	float dot_vt_m2t	= vec3f::DotProduct(velTarget, uvec_m2t);
	//// More roundabout version 
	//// With the dot product, we can determine the angle between the two vectors
	//float angle_vt_m2t	= acos(dot_vt_m2t / mag_vt);	// :NOTE: We don't need to divide by the magnitude of vt_m2t since it is a unit vector
	//// Use the angle and the target velocity vector's magnitude to get magnitude of the parallel velocity component
	//float mag_vt_p = mag_vt * cos(angle_vt_m2t);
	//// Use parallel magnitude and unit vector to determine parallel velocity vector
	//vel_target_p = mag_vt_p * uvec_m2t;

	// Next, we can project our velocity onto the parallel vector via the dot product
	vel_target_p = dot_vt_m2t * uvec_m2t;
	
	
	// Finally, we can trivially calculate the orthogonal velocity component
	vel_target_o	= velTarget - vel_target_p;
	///////////////////////////
	// Finally, determine the directional vector required for the missile intercept by calculating the orthogonal and parallel components
	vec3f vel_msl;
	vec3f vel_msl_o, vel_msl_p;

	// The orthogonal vector for our target velocity and our missile velocity must be the same!
	vel_msl_o = vel_target_o;

	// Sanity Check: Is the speed of our orthogonal vector higher than our missile's speed?
	// If so, we cannot intercept! Just return the same direction that the target is moving.
	float mag_msl_o = vel_msl_o.GetNorm();
	if (mag_msl_o > fSpeedMsl)
	{
		vel_msl = velTarget;
	}
	// Otherwise, proceed
	else
	{
		// We can determine the magnitude of the parallel missile velocity vector via pythagorean theorum
		float mag_msl_p	= (float)(sqrt((fSpeedMsl * fSpeedMsl) - (mag_msl_o * mag_msl_o)));
		// Finally, apply magnitude to unit parallel missile velocity vector
		vel_msl_p		= mag_msl_p * uvec_m2t;

		// The missile velocity is composed of the orthogonal and parallel component velocities
		vel_msl = vel_msl_o + vel_msl_p;
	}
	// Normalize & return
	return ((1.0f / vel_msl.GetNorm()) * vel_msl);
}

// DEBUG
void vec3f::Print()
{
#if defined _DEBUG
	printf("(%f, %f, %f)\n", x(), y(), z());
#endif
}

////////////////////
// CLASS: vec4f
////////////////////

// Setup & Initialization
vec4f::vec4f(float x /*= 0.0f*/, float y /*= 0.0f*/, float z /*= 0.0f*/, float w /*=0.0f*/) :
	m_vec{x,y,z,w}
{
}

// Accessor
float vec4f::operator[](int idx) const
{
	return m_vec[idx];
}

float& vec4f::operator[](int idx)
{
	return m_vec[idx];
}

float vec4f::DotProduct(const vec4f v1, const vec4f v2)
{
	float val_dp = 0;
	for (int i = 0; i < 4; i++)
	{
		val_dp += (v1[i] * v2[i]);
	}
	return val_dp;
}

/*
vec3f vec3f::CrossProduct(const vec3f v1, const vec3f v2)
{
	return vec3f
		(
			(v1.y() * v2.z()) - (v1.z() * v2.y()),
			(v1.z() * v2.x()) - (v1.x() * v2.z()),
			(v1.x() * v2.y()) - (v1.y() * v2.x())
			);
}
*/

float vec4f::GetNorm() const
{
	return sqrt(DotProduct(*this, *this));
}
void vec4f::Normalize()
{
	float vec_norm = GetNorm();
	for (int i = 0; i < 4; i++)
	{
		m_vec[i] /= vec_norm;
	}
}

// Operator Overload: Add
vec4f operator+(const vec4f v1, const vec4f v2)
{
	return vec4f(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z(), v1.w() + v2.w());
}
// Operator Overload: Subtract
vec4f operator-(const vec4f v1, const vec4f v2)
{
	return vec4f(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z(), v1.w() - v2.w());
}

// Operator Overload: Scalar Multiplication
vec4f operator*(const float fScalar, const vec4f vec)
{
	return vec4f(fScalar * vec.x(), fScalar * vec.y(), fScalar * vec.z(), fScalar * vec.w());
}

// DEBUG
void vec4f::Print()
{
#if defined _DEBUG
	printf("(%f, %f, %f, %f)\n", x(), y(), z(), w());
#endif
}