#pragma once
namespace gaia {
	struct Rect {
		float x, y, w, h;
		Rect() : x(0), y(0), w(0), h(0) {}
		Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
		Rect(const SDL_FRect& r) : x(r.x), y(r.y), w(r.w), h(r.h) {}
		Rect operator+(const Rect& other) const {
			return Rect(x + other.x, y + other.y, w + other.w, h + other.h);
		}
		Rect operator-(const Rect& other) const {
			return Rect(x - other.x, y - other.y, w - other.w, h - other.h);
		}
		Rect operator*(float scalar) const {
			return Rect(x * scalar, y * scalar, w * scalar, h * scalar);
		}
		Rect operator/(float scalar) const {
			return Rect(x / scalar, y / scalar, w / scalar, h / scalar);
		}
		bool operator==(const Rect& other) const {
			return x == other.x && y == other.y && w == other.w && h == other.h;
		}
		bool operator!=(const Rect& other) const {
			return !(*this == other);
		}
		SDL_FRect toSDL() const {
			return SDL_FRect{ x, y, w, h };

			

		}
	};
	using rect = Rect<float>;
	using irect = Rect<int>;
}