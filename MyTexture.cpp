#include "MyTexture.h"

MyTexture::MyTexture(){
	this->width = 0;
	this->height = 0;
	this->texture = NULL;
}

MyTexture::MyTexture(SDL_Renderer* renderer, std::string filePath){
	this->loadTexture(renderer, filePath);
}


MyTexture::MyTexture(SDL_Renderer* renderer, MyTexture* other){
	this->width = other->getWidth();
	this->height = other->getHeight();
	//this->texture = new  
}

MyTexture::~MyTexture(){
	
}

void MyTexture::loadTexture(SDL_Renderer* renderer, std::string filePath){
	
	SDL_Surface* tempSurface = IMG_Load( filePath.c_str());
	
	if(tempSurface == NULL){
		std::cout << "Error could not load texture: " << filePath << " " << SDL_GetError() << std::endl;
	}
	
	this->height = tempSurface->h;
	this->width = tempSurface->w;
	
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if(this->texture == NULL){
		std::cout << "Could not create texture: " << SDL_GetError() << std::endl;
	}
	
	SDL_FreeSurface(tempSurface);

}

void MyTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip){
	
	SDL_Rect drawRegion = {x, y, this->width, this->height};
	
	if(clip != NULL){
		drawRegion.w = clip->w;
		drawRegion.h = clip->h;
	}
	
	SDL_RenderCopy(renderer, this->texture, clip, &drawRegion);	
}

int MyTexture::getHeight(){
	return this->height;
}

int MyTexture::getWidth(){
	return this->width;
}

SDL_Texture* MyTexture::getTexture(){
	return this->texture;
}