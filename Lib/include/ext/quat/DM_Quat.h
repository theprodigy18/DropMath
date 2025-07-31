#pragma once

#include "../DM_Common.h"
#include "../DM_Constant.h"

#include "../vec/DM_Vec3.h"

namespace DropMath
{
	struct alignas(16) Quat
	{
		union
		{
            float4 v; // Don't ever use this directly unless you know about SSE alignment.
			struct
			{
				float x, y, z, w;
			};
		};

		// Construct identity Quat(0, 0, 0, 1);
		Quat() : v(_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)) {}
        Quat(float x, float y, float z, float w) : v(_mm_set_ps(w, z, y, x)) {}

		Quat operator+(const Quat& q) const { return Quat(_mm_add_ps(v, q.v)); }
		Quat operator*(float s) const { return Quat(_mm_mul_ps(v, _mm_set1_ps(s))); }
		Quat operator*(const Quat& q) const;

        // Return quat data so you can use it directly as a float array.
        float* Data() { return &x; }

        // Return quat data so you can use it directly as a float array.
        const float* Data() const { return &x; }

		float LengthSquared() const;
		
		float Length() const;

		// Normalize the length of the Quat to 1.
		void Normalize();

		// Return a new normalized Quat.
        Quat Normalized() const;

		// Reverse the sign of x, y, z components.
		Quat Conjugated() const { return Quat(_mm_set_ps(w, -z, -y, -x)); }

		// Return the inverse of the Quat.
		Quat Inversed() const;

		// Rotate a vector by the Quat. Returns that new vector.
		Vec3 RotateVector(const Vec3& v) const;

		// Return the dot product of two Quats.
		static float Dot(const Quat& a, const Quat& b);

		// Return the linear interpolation between two Quats.
		static Quat Lerp(const Quat& a, const Quat& b, float t);

		// Create a Quat from an axis and angle. Axis will be normalized by this function.
		static Quat FromAxisAngle(const Vec3& axis, float rad);

		// Create a Quat from an axis and angle. Axis must be normalized by the caller.
		static Quat FromAxisAngleNormalized(const Vec3& axis, float rad);

		// Create a Quat from Euler angles. Angle must be in radians.
		static Quat FromEulerAngles(float pitch, float yaw, float roll);

		// Create a Quat from Euler angles. Angle must be in radians.
        static Quat FromEulerAngles(const Vec3& eulerAngles);

		// Create a Quat from Euler angles. Angle must be in degrees.
		static Quat FromEulerDegrees(float pitchDeg, float yawDeg, float rollDeg);

		// Create a Quat from Euler angles. Angle must be in degrees.
		static Quat FromEulerDegrees(const Vec3& eulerAnglesDeg);

		DM_CONSTEXPR explicit Quat(const float4& v) : v(v) {}
	};
} // namespace DropMath

#include "DM_Quat.inl"