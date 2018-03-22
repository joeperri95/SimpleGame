#include "Character.h"
#include "MyTexture.h"
#include <vector>

class Game{
	
private:
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect screenClip;
	Character* mainCharacter;
	std::vector<Character*> enemies;
	MyTexture* background;
	
public:
	
	Game();
	~Game();
	
	void init();
	void render();
	void update();
	void addEnemy(int x, int y, std::string filePath);
	void addEnemy(Character* c);
	void removeEnemy(int i);
	void t_setClip(int x, int y);
};