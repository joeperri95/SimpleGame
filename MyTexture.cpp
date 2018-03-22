#include "MyTexture.h"

MyTexture::MyTexture(){
	this->width = 0;
	this->height = 0;
	this->tex = NULL;
}

MyTexture::MyTexture(SDL_Renderer* renderer, std::string filePath){
	loadTexture(renderer, filePath);
}


MyTexture::~MyTexture(){
	
}

void MyTexture::loadTexture(SDL_Renderer* renderer, std::string filePath){
	
	SDL_Surface* tempSurface = IMG_Load( filePath.c_str());
	
	this->height = tempSurface->h;
	this->width = tempSurface->w;
	
	if(tempSurface == NULL){
		std::cout << "Error could not load texture: " << filePath << " " << SDL_GetError() << std::endl;
	}
	
	this->tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if(this->tex == NULL){
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
	
	SDL_RenderCopy(renderer, this->tex, clip, &drawRegion);	
}

int MyTexture::getHeight(){
	return this->height;
}

int MyTexture::getWidth(){
	return this->width;
}

SDL_Texture* MyTexture::getTexture(){
	return this->tex;
}