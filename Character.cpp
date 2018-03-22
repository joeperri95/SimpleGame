#include "Character.h"

Character::Character(){
	
	this->texture = new MyTexture();
	this->x = 0;
	this->y = 0;
	this->xVelocity = 0.0;
	this->yVelocity = 0.0;
}

Character::Character(int x, int y){
	this->x = x;
	this->y = y;
	this->xVelocity = 0.0;
	this->yVelocity = 0.0;
}

Character::Character(int x, int y, MyTexture* tex){
	this->x = x;
	this->y = y;
	this->setTexture(tex);
	this->xVelocity = 0.0;
	this->yVelocity = 0.0;
}

Character::Character(int x, int y, SDL_Renderer* renderer, std::string filePath){
	this->x = x;
	this->y = y;
	this->texture = new MyTexture(renderer, filePath);
	this->xVelocity = 0.0;
	this->yVelocity = 0.0;
}

Character::~Character(){
	
}

void Character::render(SDL_Renderer* renderer){
	this->texture->render(renderer, this->x, this->y);
}

void Character::setTexture(MyTexture *tex){
	this->texture = tex;
}

void Character::setX(int x){
	this->x = x;
}

void Character::setY(int y){
	this->y = y;
}

int Character::getX(){
	return this->x;
}

int Character::getY(){
	return this->y;
}

double Character::getXVelocity(){
	return this->xVelocity;
}

double Character::getYVelocity(){
	return this->yVelocity;
}


void Character::setXVelocity(double xV){
	this->xVelocity = xV;
}

void Character::setYVelocity(double yV){
	this->yVelocity = yV;
}

MyTexture* Character::getTexture(){
	return this->texture;
}