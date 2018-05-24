#include "MyTexture.h"

#define KEY_R 225
#define KEY_G 0
#define KEY_B 0

MyTexture::MyTexture(){
	this->width = 0;
	this->height = 0;
	this->texture = NULL;
	this->font = NULL;
	this->clip = {0,0,0,0};
}

MyTexture::MyTexture(SDL_Renderer* renderer, std::string filePath){
	this->loadTexture(renderer, filePath);
	this->clip = {0,0,width,height};
}

MyTexture::MyTexture(SDL_Texture* texture, int width, int height){
	this->texture = texture;
	this->height = height;
	this->width = width;
	this->clip = {0,0,width,height};
}

MyTexture::MyTexture(SDL_Texture* texture, int width, int height, SDL_Rect* clip){
	this->texture = texture;
	this->height = height;
	this->width = width;
	this->clip = *clip;
}

MyTexture::MyTexture(SDL_Renderer* renderer, MyTexture* other){
	this->width = other->getTotalWidth();
	this->height = other->getTotalHeight();
	this->texture = other->getTexture();
	this->clip = other->getClip();
}

MyTexture::~MyTexture(){
	
}

void MyTexture::setClip(SDL_Rect* newClip){
	
	this->clip.x = newClip->x;
	this->clip.y = newClip->y;
	this->clip.w = newClip->w;
	this->clip.h = newClip->h;
	
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
	
	SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, KEY_R, KEY_G, KEY_B));
	
	
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
	
	if(this->font == NULL){
		return;
	}
	
	SDL_Surface* tempSurface = TTF_RenderText_Solid(this->font, message.c_str(), textColor);
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	this->height = tempSurface->h;
	this->width = tempSurface->w;
	this->clip = {0,0,this->width, this->height};
}


void MyTexture::loadMessage(SDL_Renderer* renderer, SDL_Color textColor, const char* message){
	
	
	if(this->font == NULL){
		return;
	}
	
	SDL_Surface* tempSurface = TTF_RenderText_Solid(this->font, message, textColor);
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	this->height = tempSurface->h;
	this->width = tempSurface->w;
	SDL_FreeSurface(tempSurface);
	this->clip = {0,0,this->width, this->height};
}

void MyTexture::render(SDL_Renderer* renderer, SDL_Rect* destRect){
	
	SDL_RenderCopy(renderer, this->texture, &(this->clip), destRect);	
}

void MyTexture::render(SDL_Renderer* renderer, int x, int y){
	
	SDL_Rect drawRegion = {x, y, this->width, this->height};
	
	if(&(this->clip) != NULL){
		drawRegion.w = this->clip.w;
		drawRegion.h = this->clip.h;
	}
	
	SDL_RenderCopy(renderer, this->texture, &(this->clip), &drawRegion);	
}

int MyTexture::getHeight(){

	return this->clip.h;
}

int MyTexture::getWidth(){
	return this->clip.w;
}

SDL_Texture* MyTexture::getTexture(){
	return this->texture;
}

SDL_Rect MyTexture::getClip(){
	return this->clip;
}

int MyTexture::getTotalHeight(){
	return this->height;
}

int MyTexture::getTotalWidth(){
	return this->width;
}