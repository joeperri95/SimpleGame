#include "Game.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SPEED 4.0
#define TITLE "Ayy"

Game::Game(){
	
}

Game::~Game(){
	
}

void Game::init(){
	
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	
	this->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_RENDERER_ACCELERATED);
	this->renderer = SDL_CreateRenderer(this->window,-1,0);
	this->screenClip = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	
	this->background = new MyTexture(renderer, "../res/yoot.png");
	this->mainCharacter = new Character(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,this->renderer,"../res/Untitled.png");
	
	std::cout << mainCharacter->getWidth() << std::endl;
	
}


void Game::addEnemy(int x, int y, std::string filePath){
	
	Character* c = new Character(x, y, this->renderer, filePath);
	
	c->setXVelocity(0);
	c->setYVelocity(0);
	
	this->enemies.push_back(c);
	
}

void Game::addEnemy(Character* c){
	this->enemies.push_back(c);
}

void Game::render(){
	
	SDL_RenderClear(this->renderer);


	background->render(renderer,0,0,&(this->screenClip));
	
	for(std::vector<Character*>::iterator i = this->enemies.begin(); i != this->enemies.end(); ++i){
		(*i)->render(this->renderer);
	}
	
	mainCharacter->render(this->renderer);
	SDL_RenderPresent(this->renderer);
}

void Game::update(){
	
	int newX = mainCharacter->getX() + mainCharacter->getXVelocity();
	int newY = mainCharacter->getY() + mainCharacter->getYVelocity();
	
	mainCharacter->setX(newX % SCREEN_WIDTH);
	mainCharacter->setY(newY % SCREEN_HEIGHT);
	

	
	if(newX >= (SCREEN_WIDTH)){
		if((this->screenClip.x + this->screenClip.w) >= this->background->getWidth()){
			mainCharacter->setX(SCREEN_WIDTH - mainCharacter->getWidth());
			mainCharacter->setXVelocity(0);
		}
		else{
			this->t_setClip(SCREEN_WIDTH,0);
		}
	}
	else if(newX < 0){
		if(this->screenClip.x == 0){
			mainCharacter->setXVelocity(0);
			mainCharacter->setX(0);
		}
		else{
			this->t_setClip(-SCREEN_WIDTH,0);
			mainCharacter->setX(SCREEN_WIDTH);
		}
	}
	
	if(newY >= SCREEN_HEIGHT){
		this->t_setClip(0,SCREEN_HEIGHT);
	}
	else if(newY < 0){
		if(this->screenClip.y == 0){
			mainCharacter->setY(0);
			mainCharacter->setYVelocity(0);
		}
		else{
			this->t_setClip(0,-SCREEN_HEIGHT);
			mainCharacter->setY(SCREEN_HEIGHT);
		}
	}
	
}


void Game::t_setClip(int x, int y){
	this->screenClip = {this->screenClip.x + x, this->screenClip.y + y ,SCREEN_WIDTH, SCREEN_HEIGHT};
}

void Game::loop(){
	
	bool quit = false;
	SDL_Event e;
	
	//corresponds to W      A      S     D
	bool keys[4] = {false,false,false,false};
	
	while(!quit){
		
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			
			else if(e.type == SDL_KEYDOWN){
				switch(e.key.keysym.sym){
					case SDLK_w:
						keys[0] = true;
						break;
					case SDLK_a:
						keys[1] = true;
						break;
					case SDLK_s:
						keys[2] = true;
						break;
					case SDLK_d:
						keys[3] = true;
						break;
					case SDLK_q:
						SDL_Quit();
						quit = true;
						break;
				}
			}
			
			else if(e.type == SDL_KEYUP){
				switch(e.key.keysym.sym){
					case SDLK_w:
						keys[0] = false;
						break;
					case SDLK_a:
						keys[1] = false;
						break;
					case SDLK_s:
						keys[2] = false;
						break;
					case SDLK_d:
						keys[3] = false;
						break;
				}
			}
		}
		
		
		if(keys[0] && keys[2]){
			mainCharacter->setYVelocity(0);
		}
		else if(keys[0] && !keys[2]){
			mainCharacter->setYVelocity(-SPEED);
		}
		else if(!keys[0] && keys[2]){
			mainCharacter->setYVelocity(SPEED);
		}
		else{
			mainCharacter->setYVelocity(0);
		}
		
		if(keys[1] && keys[3]){
			mainCharacter->setXVelocity(0);
		}
		else if(keys[1] && !keys[3]){
			mainCharacter->setXVelocity(-SPEED);
		}
		else if(!keys[1] && keys[3]){
			mainCharacter->setXVelocity(SPEED);
		}
		else{
			mainCharacter->setXVelocity(0);
		}
		
		this->update();
		this->render();
		SDL_Delay(5);
	}
}