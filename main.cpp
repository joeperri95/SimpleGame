#include <stdio.h>
#include <SDL2/SDL.h>
#include "MyTexture.h"
#include "Character.h"
#include "Game.h"

int main(int argc, char **argv)
{
	
	int lim = 10;
	int mao = 20;
	Character* c = new Character();
	MyTexture* m = new MyTexture();
	Game* g = new Game();
	
	g->init();
	
	bool done = false;
	bool keyStates[5];
	SDL_Event e;
	
	while(!done){
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				done = true;
			}
			else if(e.type == SDL_KEYDOWN){
				
				switch(e.key.keysym.sym){
					case SDLK_w:
						
						g->t_setClip(0,10);
						break;
					case SDLK_s:
						g->t_setClip(0,-10);
						break;
					case SDLK_a:
						g->t_setClip(10,0);
						break;
					case SDLK_d:
						g->t_setClip(-10,0);
						break;
				}
				
			}
		}
			
	
		
		g->render();
		g->update();
		SDL_Delay(20);
		
	}
	
	SDL_Quit();
	return 0;
}
