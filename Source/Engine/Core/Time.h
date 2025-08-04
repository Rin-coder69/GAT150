#pragma once
#include <chrono>
namespace gaia {
	class Time {
	private:
		using clock = std::chrono::high_resolution_clock;

	public:
		Time() {
			startTime = clock::now();
			frametime = clock::now();
		}
		void Tick();
		void Reset() { startTime = clock::now(); }

		float GetTime() const { return time; }
		float GetDeltaTime() const { return deltaTime; }
	private:
		float time = 0;
		float deltaTime = 0;
		clock::time_point startTime;
		clock::time_point frametime;

	};
}