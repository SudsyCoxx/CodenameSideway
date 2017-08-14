#pragma once

#include "Matrices.hpp"
#include "Vector.hpp"

namespace MathFuncs {
	class quat : public vec4 {
	public:
		quat(float s = float(0.0)) {
			x = y = z = w = s;
		}

		quat(float x_, float y_, float z_, float w_) {
			x = x_;
			y = y_;
			z = z_;
			w = w_;
		}

		quat(const vec4& v) { x = v.x;  y = v.y;  z = v.z;  w = v.w; }

		quat(const vec3& v, const float w_ = 1.0)
		{
			x = v.x;  y = v.y;  z = v.z; w = w_;
		}

		quat(const vec2& v, const float z_, const float w_)
		{
			x = v.x;  y = v.y; z = z_; w = w_;
		}

		quat& mul(const quat& other) {
			float w_ = w * other.w - x * other.x - y * other.y - z * other.z;
			float x_ = x * other.w + w * other.x + y * other.z - z * other.y;
			float y_ = y * other.w + w * other.y + z * other.x - x * other.z;
			float z_ = z * other.w + w * other.z + x * other.y - y * other.x;

			return *this = quat(x_, y_, z_, w_);
		}

		quat& mul(const vec3& r) {
			float w_ = -x * r.x - y * r.y - z * r.z;
			float x_ = w * r.x + y * r.z - z * r.y;
			float y_ = w * r.y + z * r.x - x * r.z;
			float z_ = w * r.z + x * r.y - y * r.x;

			return *this = quat(x_, y_, z_, w_);
		}
	};

	quat conjugate(quat input) {
		return quat(-input.x, -input.y, -input.z, input.w);
	}
}
