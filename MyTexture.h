#ifndef MyTexture_H
#define MyTexture_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class MyTexture{
	
private:
	
	SDL_Texture* texture;
	int width, height;
	TTF_Font* font;
	
public:
	
	MyTexture();
	MyTexture(SDL_Texture* texture, int width, int height);
	MyTexture(SDL_Renderer* renderer, MyTexture* other);
	MyTexture(SDL_Renderer* renderer, std::string filePath);
	~MyTexture();
	
	void free();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip=NULL);
	void loadMessage(SDL_Renderer* renderer, SDL_Color textColor, std::string message);
	bool loadTexture(SDL_Renderer* renderer, std::string filePath);
	bool loadFont(SDL_Renderer* renderer, std::string filePath, int fontSize);
	
	int getWidth();
	int getHeight();
	SDL_Texture* getTexture();
};

#endif //MYTEXTURE.h