#pragma once
#include "math.h"
#include <cassert>
#include <vector>

namespace gaia {
	template<typename T>
	struct  Vector2 {

		union {
			struct {
				T x, y;
			};
			struct {
				T u, v;
			};
		};

		Vector2() = default;
		Vector2(T x, T y) : x{ x }, y{ y } {}

		T operator [] (unsigned int index) const{ assert(index < 2); return(&x)[index]; }

		T& operator [] (unsigned int index) { assert(index < 2); return(&x)[index]; };
		


		Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

		Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
		Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
		Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
		Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

		Vector2& operator += (float s) { x += s; y += s; return *this; }
		Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
		Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
		Vector2& operator /= (float s) { x /= s; y /= s; return *this; }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }
		//square root (x * x + y * y)
		/// 
		float lengthSqr() const { return(x * x) + (y * y); }
		float length() const{ return gaia::math::sqrtf(lengthSqr()); }
		/// <summary>
		/// Returns a normalized (unit length) version of the vector.
		/// </summary>
		/// <returns>A Vector2 representing the direction of the original vector with a length of 1.</returns>
		Vector2 Normalized() const { return *this / length() ; }
		/// <summary>
		/// Returns the angle, in radians, of the vector from the origin to the point (x, y).
		/// </summary>
		/// <returns>The angle in radians, computed using atan2f(y, x).</returns>
		float Angle() const { return math::atan2f(y, x); }

		Vector2 Rotate(float radians) const {
			Vector2 v;
			v.x = x * math::cosf(radians) - y * math::sinf(radians);
			v.y = x * math::sinf(radians) + y * math::cosf(radians);
			return v;
		}
	};

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}


/*Vector2<int> iv;
 Vector2<float> fv;*/
 