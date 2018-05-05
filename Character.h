#ifndef Character_H
#define Character_H

#include "MyTexture.h"
#include "GameObject.h"
#include <string>

class Character : public GameObject{
	
private:
	
	int x, y;
	double xVelocity, yVelocity;
	MyTexture* texture;	
	
public:
	
	Character();
	Character(int x, int y, SDL_Renderer* renderer, MyTexture* tex);
	Character(int x, int y, SDL_Renderer* renderer, std::string filePath);
	Character(int x, int y);
	
	~Character();
	
	void setTexture(SDL_Renderer* renderer, MyTexture* tex);
	void render(SDL_Renderer* renderer);
	void setX(int x);
	void setY(int y);
	void setXVelocity(double xV);
	void setYVelocity(double yV);
	
	MyTexture* getTexture();
	int getX();
	int getY();
	int getWidth();

	double getXVelocity();
	double getYVelocity();
};

#endif //Character_H