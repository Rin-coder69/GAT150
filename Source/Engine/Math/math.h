#pragma once
#include <algorithm>
#include <SDL3/SDL.h>
#include <cmath>
namespace gaia {
	namespace math {
		constexpr float PI = 3.14159265358979323846f;
		constexpr float TWO_PI = 2 * PI;
		constexpr float HALF_PI = PI / 2;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="rad"></param>
		/// <returns></returns>
		constexpr float radToDeg(float rad) { return rad * (180 / PI); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="deg"></param>
		/// <returns></returns>
		constexpr float degToRad(float deg) { return deg * (PI / 180); }

		constexpr int wrap(int value, int min, int max) {
			if (value > max) value = value - max;

			int range = max - min;
			int result = (value - min) % range;
			if (result < 0) result += range;

			return min + result;
		}

//Wrap function

		inline float wrap(float value, float min, float max) {
			float range = max - min;//calcylate range of a wrap
			float result = std::fmodf(value - min, range);//shift value so range starts at zero
			if (result < 0) result += range;//wrap forward if result is negative
			return min + result;//shift result back to [min,max) range
		}



		using std::min;
		using std::max;
		using std::clamp;
		using std::sqrtf;
		using std::sqrt;
		using std::cos;
		using std::sin;
		using std::atan2;
		using std::atan2f;
		using std::cosf;
		using std::sinf;



	};
}