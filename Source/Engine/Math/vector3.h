#pragma once
#include "math.h"
#include <cassert>

namespace gaia {
	template <typename T>
	struct Vector3
	{
		union {
			struct {
				T x, y, z;
			};
			struct {
				T r, g, b;
			};
		};
		Vector3() = default;
		Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } {}

		T operator [] (unsigned int index) const { assert(index < 3); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 3); return (&x)[index]; }

		Vector3 operator + (const Vector3& other) const { return Vector3(x + other.x, y + other.y, z + other.z); }
		Vector3 operator - (const Vector3& other) const { return Vector3(x - other.x, y - other.y, z - other.z); }
		Vector3 operator * (const Vector3& other) const { return Vector3(x * other.x, y * other.y, z + other.z); }
		Vector3 operator / (const Vector3& other) const { return Vector3(x / other.x, y /other.y, z / other.z); }


		Vector3 operator + (T scalar) const { return Vector3(x + scalar, y + scalar, z + scalar); }
		Vector3 operator - (T scalar) const { return Vector3(x - scalar, y - scalar, z - scalar); }
		Vector3 operator * (T scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
		Vector3 operator / (T scalar) const { assert(scalar != 0); return Vector3(x / scalar, y / scalar, z / scalar); }
	};
	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
};