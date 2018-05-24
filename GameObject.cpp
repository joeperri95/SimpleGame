#include "GameObject.h"

GameObject::GameObject(){
	this->x = 0;
	this->y = 0;
	this->texture = NULL;
}

GameObject::GameObject(int x, int y, MyTexture* tex, SDL_Renderer* renderer){
	this->x = x;
	this->y = y;
	this->texture = new MyTexture(renderer, tex);
}

GameObject::GameObject(int x, int y, std::string name, SDL_Renderer* renderer){
	this->x = x;
	this->y = y;
	
	this->texture = new MyTexture(renderer, name);
	
}

GameObject::~GameObject(){
	
}

int GameObject::getX(){
	return this->x;
}

int GameObject::getY(){
	return this->y;
}

void GameObject::render(SDL_Renderer* renderer){
	
	this->texture->render(renderer, this->x, this->y);
 	
}

void GameObject::setX(int x){
	this->x = x;
}

void GameObject::setY(int y){
	this->y = y;
}


int GameObject::getHeight(){
	return this->texture->getHeight();
}

int GameObject::getWidth(){
	return this->texture->getWidth();
}