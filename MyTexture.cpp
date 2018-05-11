#include "MyTexture.h"

MyTexture::MyTexture(){
	this->width = 0;
	this->height = 0;
	this->texture = NULL;
	this->font = NULL;
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

bool MyTexture::loadFont(SDL_Renderer* renderer, std::string filePath, int fontsize){
	
	this->font = TTF_OpenFont(filePath.c_str(), fontsize);
	if(this->font != NULL){
		return true;
	}
	
	return false;
	
}

bool MyTexture::loadTexture(SDL_Renderer* renderer, std::string filePath){
	
	SDL_Surface* tempSurface = IMG_Load(filePath.c_str());
	
	if(tempSurface == NULL){
		std::cout << "Error could not load texture: " << filePath << " " << SDL_GetError() << std::endl;
		return false;
	}
	
	this->height = tempSurface->h;
	this->width = tempSurface->w;
	
	SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0xFF, 0xFF));
	
	
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if(this->texture == NULL){
		std::cout << "Could not create texture: " << SDL_GetError() << std::endl;
		return false;
	}
	
	SDL_FreeSurface(tempSurface);
	return true;

}

void MyTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
	
	SDL_SetTextureColorMod(this->texture, red, green, blue);
	
}

void MyTexture::loadMessage(SDL_Renderer* renderer, SDL_Color textColor, std::string message){
	
	SDL_Surface* tempSurface = TTF_RenderText_Solid(this->font, message.c_str(), textColor);
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	this->height = tempSurface->h;
	this->width = tempSurface->w;
	
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