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
	int clipWidth, clipHeight;
	TTF_Font* font;
	SDL_Rect clip;
	
public:
	
	MyTexture();
	MyTexture(SDL_Texture* texture, int width, int height);
	MyTexture(SDL_Texture* texture, int width, int height, SDL_Rect* clip);
	MyTexture(SDL_Renderer* renderer, MyTexture* other);
	MyTexture(SDL_Renderer* renderer, std::string filePath);
	~MyTexture();
	
	void free();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setClip(SDL_Rect* clip);
	void render(SDL_Renderer* renderer, int x, int y);
	void render(SDL_Renderer* renderer, SDL_Rect* destRect);
	void loadMessage(SDL_Renderer* renderer, SDL_Color textColor, std::string message);
	void loadMessage(SDL_Renderer* renderer, SDL_Color textColor, const char* message);
	bool loadTexture(SDL_Renderer* renderer, std::string filePath);
	bool loadFont(SDL_Renderer* renderer, std::string filePath, int fontSize);
	
	int getWidth();
	int getHeight();
	int getTotalWidth();
	int getTotalHeight();
	SDL_Texture* getTexture();
	SDL_Rect getClip();
};

#endif //MYTEXTURE.h