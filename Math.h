#pragma once

#include <math.h>
#include "Vector.h"
#include <iostream>
#include <Windows.h>
#include "Structs.h"
#include "Definitions.h"
#include "Enums.h"
#include <xmmintrin.h> 
#include "InputSystem.h"

class CMath
{
public:
	void inline SinCos(float Rads, float *Sine, float *Cosine);
	void AngleVectors(const QAngle &Angles, Vector &Forward);
	float GetFov(const QAngle &LocalAngle, const QAngle &DestinationAngle);
	void VectorAngles(const Vector &Forward, QAngle &Angles);
	QAngle CalcAngle(Vector Source, Vector Distance);
	void VectorTransform(Vector& in1, matrix3x4a_t& in2, Vector &Out);
}; extern CMath g_Math;