#pragma once
#ifndef MATH3D_H
#define MATH3D_H

#include "vec.h"
#include "quat.h"

// FILE: math3d.h
// DESC: Applied 3D (& 2D for now) Math

// 3D Target Intercept
vec3f GetTargetIntercept(vec3f posMsl, float fSpeedMsl, vec3f posTarget, vec3f velTarget);
float GetInterceptTime(vec3f pos1, vec3f vel1, vec3f pos2, vec3f vel2);
vec3f GetInterceptPoint(vec3f posSrc, vec3f velSrc, vec3f posTarget, vec3f velTarget);

// 2D
bool IsWithinRange2D(vec2f posSentry, vec2f dirSentry, float rangeSentry, float halfAngleSentry, vec2f posCheck);

#endif	// #define MATH3D_H