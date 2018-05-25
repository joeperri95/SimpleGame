#ifndef Character_H
#define Character_H

#include "Bullet.h"
#include "MyTexture.h"
#include "GameObject.h"
#include "Timer.h"
#include <string>

enum PlayerState{
	IDLE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
	
};


class Character : public GameObject{
	
private:
	
	int x, y;
	bool immune;
	Uint32 lastShot;
	int health;
	double xVelocity, yVelocity;
	MyTexture* texture;	
	PlayerState state;
	
	
public:
	
	Bullet* b;
	
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
	void setHealth(int newHealth);
	void takeDamage(int damage);
	void setImmune(bool in);
	void shoot(SDL_Renderer* renderer);
	MyTexture* getTexture();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getHealth();
	
	bool isAlive();
	bool isImmune();
	
	double getXVelocity();
	double getYVelocity();
};

#endif //Character_H