
namespace DropMath
{
    inline Quat Quat::operator*(const Quat& q) const
    {
        return Quat(
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w,
            w * q.w - x * q.x - y * q.y - z * q.z);
    }

    inline float Quat::LengthSquared() const { return _mm_cvtss_f32(_mm_dp_ps(v, v, DOT_MASK)); }

    inline float Quat::Length() const
    {
        float4 dot = _mm_dp_ps(v, v, DOT_MASK);
        return _mm_cvtss_f32(_mm_sqrt_ss(dot));
    }

    inline void Quat::Normalize()
    {
        float len = Length();
        if (len > F::EPSILON)
        {
            v = _mm_div_ps(v, _mm_set1_ps(len));
        }
    }

    inline Quat Quat::Normalized() const
    {
        Quat q = *this;
        q.Normalize();
        return q;
    }

	inline Quat Quat::Inversed() const
	{
        return Conjugated() * (1.0f / LengthSquared());
	}

	inline Vec3 Quat::RotateVector(const Vec3& v) const
	{
        Quat q = Quat(_mm_set_ps(0.0f, v.z, v.y, v.x));
        Quat result = (*this) * q * (*this).Conjugated();
		return Vec3(result.x, result.y, result.z);
	}

	inline float Quat::Dot(const Quat& a, const Quat& b)
	{
		return _mm_cvtss_f32(_mm_dp_ps(a.v, b.v, DOT_MASK));
	}

	inline Quat Quat::Lerp(const Quat& a, const Quat& b, float t) { return DropMath::Lerp(a, b, t).Normalized(); }

    inline Quat Quat::FromAxisAngle(const Vec3& axis, float rad)
    {
        rad       = rad * 0.5f;
        float sin = Sin(rad);
        float cos = Cos(rad);

        Vec3 v = axis.Normalized();

        return Quat(
            v.x * sin,
            v.y * sin,
            v.z * sin,
            cos);
    }

	inline Quat Quat::FromAxisAngleNormalized(const Vec3& axis, float rad)
    {
        rad       = rad * 0.5f;
        float sin = Sin(rad);
        float cos = Cos(rad);

        return Quat(
            axis.x * sin,
            axis.y * sin,
            axis.z * sin,
            cos);
    }

	inline Quat Quat::FromEulerAngles(float pitch, float yaw, float roll)
	{
		float sx = Sin(pitch * 0.5f);
		float sy = Sin(yaw * 0.5f);
		float sz = Sin(roll * 0.5f);

		float cx = Cos(pitch * 0.5f);
		float cy = Cos(yaw * 0.5f);
		float cz = Cos(roll * 0.5f);

		return Quat(
			sx * cy * cz + cx * sy * sz,
			cx * sy * cz - sx * cy * sz,
			cx * cy * sz + sx * sy * cz,
			cx * cy * cz - sx * sy * sz
		);
	}

	inline Quat Quat::FromEulerAngles(const Vec3& eulerAngles)
	{
		return FromEulerAngles(eulerAngles.x, eulerAngles.y, eulerAngles.z);
	}

	inline Quat Quat::FromEulerDegrees(float pitchDeg, float yawDeg, float rollDeg)
	{
        return FromEulerAngles(ToRadians(pitchDeg), ToRadians(yawDeg), ToRadians(rollDeg));
	}

	inline Quat Quat::FromEulerDegrees(const Vec3& eulerAnglesDeg)
	{
		return FromEulerAngles(ToRadians(eulerAnglesDeg.x), ToRadians(eulerAnglesDeg.y), ToRadians(eulerAnglesDeg.z));
	}

} // namespace DropMath