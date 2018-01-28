#include "math3d.h"

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
	vec3f vec_m2t = posTarget - posMsl;
	// Convert to unit vector
	vec3f uvec_m2t = (1.0f / vec_m2t.GetNorm()) * vec_m2t;
	// Also, calculate the target velocity's magnitude for later
	float mag_vt = velTarget.GetNorm();

	///////////////////////////
	// Next, project the target velocity onto the m2t vector to determine parallel (p) & orthogonal (o) component vectors
	vec3f vel_target_o, vel_target_p;

	// Start by calculating the dot product between our target velocity vector and the m2t vector
	float dot_vt_m2t = vec3f::DotProduct(velTarget, uvec_m2t);
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
	vel_target_o = velTarget - vel_target_p;
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
		float mag_msl_p = (float)(sqrt((fSpeedMsl * fSpeedMsl) - (mag_msl_o * mag_msl_o)));
		// Finally, apply magnitude to unit parallel missile velocity vector
		vel_msl_p = mag_msl_p * uvec_m2t;

		// The missile velocity is composed of the orthogonal and parallel component velocities
		vel_msl = vel_msl_o + vel_msl_p;
	}
	// Normalize & return
	return ((1.0f / vel_msl.GetNorm()) * vel_msl);
}

/**
*	Calculates time until interception for two entities given their positions and velocities
*	@return	Time until interception
*/
float GetInterceptTime(vec3f pos1, vec3f vel1, vec3f pos2, vec3f vel2)
{
	// First, calculate vector from one entity to the other
	vec3f vec_dir = pos2 - pos1;
	// Convert to unit vector
	vec3f uvec_dir = (1.0f / vec_dir.GetNorm()) * vec_dir;

	// Project our two velocity vectors onto the direction vector
	vec3f vel_p_1, vel_p_2;	// Parallel component vectors for vel1 & vel2
	vel_p_1 = (vec3f::DotProduct(vel1, uvec_dir) * uvec_dir);
	vel_p_2 = (vec3f::DotProduct(vel2, uvec_dir) * uvec_dir);

	// Determine intercept parallel velocity: how much closer the two targets become on the parallel axis
	vec3f vel_intercept_p = vel_p_2 - vel_p_1;
	float mag_intercept_p = vel_intercept_p.GetNorm();
	// Divide initial distance between the entities by the scalar speed of parallel intercepts to determine how long until intercept
	return (vec_dir.GetNorm() / mag_intercept_p);
}

/**
 *	@param posSrc	Source position
**/
vec3f GetInterceptPoint(vec3f pos1, vec3f vel1, vec3f pos2, vec3f vel2)
{
	// Determine time until intercept
	float intercept_time = GetInterceptTime(pos1, vel1, pos2, vel2);

	// Simply apply time until intercept to the velocity and add it to initial position (could also be done wi/ pos2)
	vec3f point_intercept = pos1 + (intercept_time * vel1);
	return point_intercept;
}

/**
 * Detect if posCheck position is within the vision range of the sentry.
 * @param	posSentry	Position of sentry
 * @param	dirSentry	Direction vector the sentry is facing
 * @param	rangeSentry	Distance the sentry can see along its path
**/
bool IsWithinRange2D(vec2f posSentry, vec2f dirSentry, float rangeSentry, float halfAngleSentry, vec2f posTarget)
{
	// Check: Range
	vec2f vec_distance	= posTarget - posSentry;
	float f_distance_sq = vec_distance.x * vec_distance.x + vec_distance.y * vec_distance.y;
	// If we're outside the maximum range of the sentry, we can exit early and improve performance
	if (f_distance_sq > (rangeSentry * rangeSentry))	// :NOTE: Compare squared values of distance and range to avoid an unnecessary sqrt calculation
	{
		return false;
	}

	// Check: Direction
	// Use dot product between dirSentry & vec_distance to determine angle between the two vectors
	float dp	= vec2f::DotProduct(dirSentry, vec_distance);
	// Angle between the direction sentry is facing and the direction towards the target
	float angle = acosf(dp / (dirSentry.GetNorm() * vec_distance.GetNorm()));	// :NOTE: Can be optimized to avoid acos calculation, I think?

	return (angle <= halfAngleSentry);
}


float Lerp(float f1, float f2, float t)
{
	return (((1.0f - t) * f1) + (t * f2));
}

/**
 *	Perform linear interpolation between two 2D points on range [0.0f,1.0f]
 *	@param p0	Initial position (2D)
 *	@param p1	Ending position (2D)
 *	@param t	
**/
vec2f Lerp2D(vec2f p0, vec2f p1, float t)
{
	//assert(t >= 0.0f && t <= 1.0f);

	// Determine X & Y values based on t
	vec2f point;
	point.x = ((1.0f - t) * p0.x) + (t * p1.x);
	point.y = ((1.0f - t) * p0.y) + (t * p1.y);

	return point;
}

/**
*	Perform linear interpolation between two 3D points on range [0.0f,1.0f]
*	@param p0	Initial position (3D)
*	@param p1	Ending position (3D)
*	@param t
**/
vec3f Lerp3D(vec3f p0, vec3f p1, float t)
{
	//assert(t >= 0.0f && t <= 1.0f);

	// Determine X & Y values based on t
	vec3f point;
	point.x() = ((1.0f - t) * p0.x()) + (t * p1.x());
	point.y() = ((1.0f - t) * p0.y()) + (t * p1.y());
	point.z() = ((1.0f - t) * p0.z()) + (t * p1.z());

	return point;
}