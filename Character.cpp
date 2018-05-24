#include "Character.h"

Character::Character() : GameObject() {
	
	this->texture = new MyTexture();
	this->x = 0;
	this->y = 0;
	this->health = 0;
	this->immune = false;
	this->state = IDLE;
	this->xVelocity = 0.0;
	this->yVelocity = 0.0;
}

Character::Character(int x, int y, SDL_Renderer* renderer, MyTexture* tex) : GameObject(x, y, tex, renderer){
	this->x = x;
	this->y = y;
	this->health = 3;
	this->immune = false;
	this->setTexture(renderer, tex);
	this->state = IDLE;
	this->xVelocity = 0.0;
	this->yVelocity = 0.0;
}

Character::Character(int x, int y, SDL_Renderer* renderer, std::string filePath){
	this->x = x;
	this->y = y;
	this->health = 3;
	this->immune = false;
	this->texture = new MyTexture(renderer, filePath);
	this->state = IDLE;
	this->xVelocity = 0.0;
	this->yVelocity = 0.0;
}

Character::~Character(){
	
}
 
void Character::render(SDL_Renderer* renderer){
	
	SDL_Rect clip = {0,0,0,0};
	
	switch(this->state){
		case IDLE:
			clip = {0,0,32,32};
		break;
		case LEFT:
			clip = {32,0,32,32};
		break;
		case RIGHT:
			clip = {0,0,32,32};
		break;
		case UP:
			clip = {96,0,32,32};
		break;
		case DOWN:
			clip = {64,0,32,32};
		break;
		default:
			clip = {0,0,32,32};
		break;
	}
	
	this->texture->setClip(&clip);
	this->texture->render(renderer, this->x, this->y);
}

void Character::takeDamage(int damage){
	if(this->immune){
		return;
	}
	else{
		this->setHealth(this->getHealth() - damage);
		
		if(this->isAlive()){
			this->immune = true;
		}
	}
}

void Character::setImmune(bool in){
	this->immune = in;
}

void Character::setHealth(int newHealth){
	this->health = newHealth;
}

void Character::setTexture(SDL_Renderer* renderer, MyTexture *tex){
	this->texture = new MyTexture(renderer, tex);
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

int Character::getHealth(){
	return this->health;
}

double Character::getXVelocity(){
	return this->xVelocity;
}

double Character::getYVelocity(){
	return this->yVelocity;
}

bool Character::isAlive(){
	return this->health > 0;
}

bool Character::isImmune(){
	return this->immune;
}

void Character::setXVelocity(double xV){
	
	if(xV > 0){
		state = RIGHT;
	}
	else if(xV < 0){
		state = LEFT;
	}
	else{
		//state = IDLE;
	}
	
	this->xVelocity = xV;
}

void Character::setYVelocity(double yV){
	
	if(yV > 0){
		state = DOWN;
	}
	else if(yV < 0){
		state = UP;
	}
	else{
		//state = IDLE;
	}
	
	this->yVelocity = yV;
}

MyTexture* Character::getTexture(){
	return this->texture;
}

int Character::getWidth(){
	return this->texture->getWidth();
}


int Character::getHeight(){
	return this->texture->getHeight();
}
