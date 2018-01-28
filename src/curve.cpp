#include "curve.h"
#include "math3d.h"

const mat33 Bezier2DQuad::MAT_QUAD = mat33
(
	vec3f(1.0f, -2.0f, 1.0f),
	vec3f(-2.0f, 2.0f, 0.0f),
	vec3f(1.0f, 0.0f, 0.0f)
);

const mat44 Bezier2DCube::MAT_CUBE = mat44
(
	vec4f(-1.0f, 3.0f, -3.0f, 1.0f),
	vec4f(3.0f, -1.0f, 3.0f, 0.0f),
	vec4f(-3.0f, 3.0f, 0.0f, 0.0f),
	vec4f(1.0f, 0.0f, 0.0f, 0.0f)
	);

Bezier2DQuad::Bezier2DQuad(vec2f p1, vec2f p2, vec2f p3)
{
	// Store control values as points
	m_controls[0] = p1;
	m_controls[1] = p2;
	m_controls[2] = p3;

	// Store control values as X/Y vectors
	m_controlX = vec3f(p1.x, p2.x, p3.x);
	m_controlY = vec3f(p1.y, p2.y, p3.y);
}

vec2f Bezier2DQuad::GetPoint(float t)
{
	//// BASIC
	//// Calculate points for line
	//vec2f p1 = Lerp2D(m_controls[0], m_controls[1], t);
	//vec2f p2 = Lerp2D(m_controls[1], m_controls[2], t);

	//vec2f point = Lerp2D(p1, p2, t);

	//return point;

	// ADVANCED
	vec3f vec_t(t * t, t, 1);
	vec3f vec_t_quad = MAT_QUAD * vec_t;

	vec2f vec_point(vec3f::DotProduct(m_controlX,vec_t_quad), vec3f::DotProduct(m_controlY, vec_t_quad));
	return vec_point;
}


Bezier2DCube::Bezier2DCube(vec2f p1, vec2f p2, vec2f p3, vec2f p4)
{
	// Store control values as points
	m_controls[0] = p1;
	m_controls[1] = p2;
	m_controls[2] = p3;
	m_controls[4] = p4;

	// Store control values as X/Y vectors
	m_controlX = vec4f(p1.x, p2.x, p3.x, p4.x);
	m_controlY = vec4f(p1.y, p2.y, p3.y, p4.y);
}

vec2f Bezier2DCube::GetPoint(float t)
{
	vec4f vec_t(t * t * t, t * t, t, 1);
	vec4f vec_t_cube = MAT_CUBE * vec_t;

	vec2f vec_point(vec4f::DotProduct(m_controlX, vec_t_cube), vec4f::DotProduct(m_controlY, vec_t_cube));
	return vec_point;
}