#include "Time.h"
namespace gaia {
	void gaia::Time::Tick()
	{
		clock::time_point now = clock::now();
		time = std::chrono::duration<float>(now - startTime).count();
		deltaTime = std::chrono::duration<float>(now - frametime).count();
		frametime = now;
	}
}
