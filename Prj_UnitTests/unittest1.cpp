#include "stdafx.h"
#include "CppUnitTest.h"

#include "../src/math3d.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_3DGEP
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		// Test 1: Directly behind sentry
		TEST_METHOD(WithinRange01)
		{
			// Facing forward along X-axis
			vec2f v_sentry(0.0f, 0.0f);
			vec2f v_dir(1.0f, 0.0f);

			// Behind on X-axis, but within distance
			vec2f v_target(-0.1f, 0.0f);
			Assert::IsFalse(IsWithinRange2D(v_sentry, v_dir, 1.5f, M_PI_4, v_target));
		}

	};
}