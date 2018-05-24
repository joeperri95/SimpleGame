#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "MyTexture.h"
#include "Character.h"
#include "Game.h"


void test();

int main(int argc, char **argv)
{
	
	//test();
	
	Game* g = new Game();
	
	g->init();
	g->loop();
	
	return 0;
}

void test(){
	
	
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();	
	
	std::string s = "abcdefghijklmnopqrstuvwxyz";
	SDL_Window* window = SDL_CreateWindow("abcdefghijklmnopqrstuvwxyz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_RENDERER_ACCELERATED);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
	
	SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
	
	MyTexture* a = new MyTexture();
	a->loadFont(renderer, "../res/lazy.ttf", 28);
	int cnt = 0;
	
	bool quit = false;
	
	while(!quit){
		
		
		
		SDL_RenderClear(renderer);
		a->loadMessage(renderer, textColor, std::to_string(cnt));
		a->render(renderer, 0, 0);

		SDL_RenderPresent(renderer);
		cnt++;
		SDL_Delay(1000);
		
	}
	
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	
}

