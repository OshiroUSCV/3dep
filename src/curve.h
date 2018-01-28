#include "mat.h"

// CLASS: BezierCurve2D (ABSTRACT)
// All Bezier curves will operate in the range of [0.0f,1.0f]
// Any value in this range will return a 2D point.
class BezierCurve2D
{
public: 
	virtual vec2f GetPoint(float t) =0;
};


// CLASS: Bezier2DQuad
// Bezier curve w/ 3 control points
class Bezier2DQuad : public BezierCurve2D
{
protected:
	vec2f m_controls[3];	// As points (Redundant)
	vec3f m_controlX;		// As x-values
	vec3f m_controlY;		// As y-values

	// Quadratic Multiplication Matrix
	static const mat33 MAT_QUAD; 
public:
	Bezier2DQuad(vec2f p1, vec2f p2, vec2f p3);

	vec2f GetPoint(float t);
};

// CLASS: Bezier2DCube
// Bezier curve w/ 4 control points
class Bezier2DCube : public BezierCurve2D
{
protected:
	vec2f m_controls[4];	// As points (Redundant)
	vec4f m_controlX;		// As x-values
	vec4f m_controlY;		// As y-values

							// Quadratic Multiplication Matrix
	static const mat44 MAT_CUBE;
public:
	Bezier2DCube(vec2f p1, vec2f p2, vec2f p3, vec2f p4);

	vec2f GetPoint(float t);
};

////////////////////////////////////////////////////////////////////

// CLASS: BezierCurve3D (ABSTRACT)
// All Bezier curves will operate in the range of [0.0f,1.0f]
// Any value in this range will return a 3D point.
class BezierCurve3D
{
public:
	virtual vec3f GetPoint(float t) = 0;
};