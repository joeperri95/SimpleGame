#include "MyTexture.h"
#include <string>

class GameObject{
	
private:
	
	int x,y;
	MyTexture* texture;
	
public:
	
	GameObject();
	GameObject(int x, int y, MyTexture* tex, SDL_Renderer* renderer);
	GameObject(int x, int y, std::string name, SDL_Renderer* renderer);
	
	~GameObject();
	
	void render(SDL_Renderer* renderer);

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	
	void setX(int x);
	void setY(int y);
	
};