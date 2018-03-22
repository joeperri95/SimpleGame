#ifndef MyTexture_H
#define MyTexture_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class MyTexture{
	
private:
	
	SDL_Texture* tex;
	int width, height;
	
public:
	
	MyTexture();
	MyTexture(SDL_Renderer* renderer, std::string filePath);
	~MyTexture();
	
	void free();
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip=NULL);
	void loadTexture(SDL_Renderer* renderer, std::string filePath);
	int getWidth();
	int getHeight();
	SDL_Texture* getTexture();
};

#endif //MYTEXTURE.h