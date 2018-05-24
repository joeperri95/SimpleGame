#include "Character.h"
#include "MyTexture.h"
#include <vector>
#include <string>
#include <sstream>	

enum GameState{
	
	Menu,
	Startup,
	Running,
	Pause,
	GameOver
	
};

class Game{
	
private:
	
	GameState state;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect screenClip;
	Character* mainCharacter;
	std::vector<Character*> enemies;
	std::vector<GameObject*> scenery;
	MyTexture* background;
	MyTexture* hearts;
	MyTexture* gameOverFont;
	MyTexture* pauseFont;
	Timer* fpsTimer;
	Timer* immuneTimer;
	int countedFrames;
	
public:
	
	Game();
	~Game();
	
	void init();
	void render();
	void update();
	void loop();
	void addEnemy(int x, int y, std::string filePath);
	void addEnemy(Character* c);
	void addScenery(GameObject* g);
	void removeEnemy(int i);
	void t_setClip(int x, int y);
};