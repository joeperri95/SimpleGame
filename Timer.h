#include <SDL2/SDL.h>

class Timer{
	
private:
	
	Uint32 startTicks;
	Uint32 pausedTicks;
	
	bool paused;
	bool started;
	
	public:
	
	Timer();
	~Timer();
	
	void start();
	void stop();
	void pause();
	void unpause();
	
	Uint32 getTicks();
	
	bool isPaused();
	bool isRunning();
	
};